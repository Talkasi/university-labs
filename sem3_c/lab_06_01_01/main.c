#include "my_film.h"
#include <stdio.h>
#include <string.h>

#define MAX_NFILMS 15

#define WRONG_NARGS_ERR -1
#define OPEN_FILE_ERR -2
#define READ_DATA_ERR -3

#define PROGRAM_NAME 0
#define FILE_NAME 1
#define FIELD 2
#define KEY 3

int field_check(char *field);

int main(int argc, char **argv)
{
    if (argc == 3 || argc == 4)
    {
        int field_key = field_check(argv[FIELD]);
        if (field_key < 0)
            return field_key;

        FILE *f = fopen(argv[FILE_NAME], "r");
        if (f == NULL)
            return OPEN_FILE_ERR;

        film_t sorted_films[MAX_NFILMS];
        size_t n_films;

        if (fread_data_to_arr(f, sorted_films, MAX_NFILMS, &n_films, field_key) || n_films == 0)
        {
            fclose(f);
            return READ_DATA_ERR;
        }

        fclose(f);
        if (argc == 3)
        {
            films_print(sorted_films, n_films);
            return 0;
        }
        else
        {
            size_t index;
            int rc = films_bin_search(sorted_films, n_films, field_key, argv[KEY], &index);

            if (rc < 0)
                return rc;

            if (index < n_films)
                film_print(&sorted_films[index]);
            else
                printf("Not found\n");
        }
    }
    else
        return WRONG_NARGS_ERR;

    return 0;
}

int field_check(char *field)
{
    if (strcmp(field, "title") == 0)
        return TITLE;
    if (strcmp(field, "name") == 0)
        return NAME;
    if (strcmp(field, "year") == 0)
        return YEAR;

    return WRONG_FIELD_ERR;
}
