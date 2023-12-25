#include "film.h"
#include <stdio.h>
#include <string.h>

enum main_errs
{
    WRONG_NARGS_ERR = -10,
    OPEN_FILE_ERR,
    READ_DATA_ERR
};

enum args
{
    PROGRAM_NAME,
    FILE_NAME,
    FIELD,
    KEY
};

field_args_t field_check(char *field);

int main(int argc, char **argv)
{
    if (argc != 3 && argc != 4)
        return WRONG_NARGS_ERR;

    field_args_t field_key = field_check(argv[FIELD]);
    if (field_key == INVALID)
        return WRONG_FIELD_ERR;

    FILE *f = fopen(argv[FILE_NAME], "r");
    if (f == NULL)
        return OPEN_FILE_ERR;

    film_t *sorted_films = NULL;
    size_t n_films;

    int rc;

    if ((rc = fread_data_to_arr(f, &sorted_films, &n_films, field_key)) || n_films == 0)
    {
        fclose(f);
        return rc;
    }

    fclose(f);
    if (argc == 3)
        films_print(sorted_films, n_films);

    if (argc == 4)
    {
        size_t index;
        int rc = films_bin_search(sorted_films, n_films, field_key, argv[KEY], &index);

        if (rc < 0)
        {
            free_films(sorted_films, n_films);
            return rc;
        }

        if (index < n_films)
            film_print(&sorted_films[index]);
        else
            printf("Not found\n");
    }

    free_films(sorted_films, n_films);
    return 0;
}

field_args_t field_check(char *field)
{
    if (strcmp(field, "title") == 0)
        return TITLE;
    if (strcmp(field, "name") == 0)
        return NAME;
    if (strcmp(field, "year") == 0)
        return YEAR;

    return INVALID;
}
