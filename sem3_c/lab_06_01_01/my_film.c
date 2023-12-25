#include "my_film.h"
#include <string.h>

size_t fread_line(FILE *f, char *s, size_t max_len)
{
    char tmp[MAX_STR_LEN];
    if (max_len > MAX_STR_LEN)
        return 0;

    if (fgets(tmp, MAX_STR_LEN, f) == NULL)
        return 0;

    size_t len_tmp = strlen(tmp);
    if (tmp[len_tmp - 1] != '\n')
        return 0;

    tmp[--len_tmp] = '\0';
    if (len_tmp >= max_len)
        return 0;

    strcpy(s, tmp);
    return len_tmp;
}

int film_read(FILE *f, film_t *film)
{
    if (fread_line(f, film->title, MAX_TITLE_LEN) == 0)
        return NO_FILM_ERR;
    if (fread_line(f, film->name, MAX_NAME_LEN) == 0)
        return WRONG_FILM_ERR;
    if (fscanf(f, "%d\n", &film->year) != 1 || film->year < 0)
        return WRONG_FILM_ERR;

    return 0;
}

void film_rshift(film_t films[], size_t i_left, size_t i_right)
{
    for (size_t j = i_right; j > i_left; --j)
        films[j] = films[j - 1];
}

int fread_data_to_arr(FILE *f, film_t films[], size_t max_nfilms, size_t *n_films, int field)
{
    *n_films = 0;
    if (field != TITLE && field != NAME && field != YEAR)
        return WRONG_FIELD_ERR;

    rewind(f);
    if (film_read(f, &films[0]) != 0)
        return ferror(f) != 0;

    ++*n_films;
    int rc;
    film_t tmp;
    while ((rc = film_read(f, &tmp)) == 0)
    {
        if (*n_films + 1 > max_nfilms)
            return *n_films + 1;

        for (size_t i = *n_films; i > 0; --i)
        {
            if ((field == TITLE && strcmp(tmp.title, films[i - 1].title) >= 0) ||
                (field == NAME && strcmp(tmp.name, films[i - 1].name) >= 0) ||
                (field == YEAR && tmp.year >= films[i - 1].year))
            {
                film_rshift(films, i, *n_films);
                films[i] = tmp;
                break;
            }
            else if (i == 1)
            {
                film_rshift(films, 0, *n_films);
                films[0] = tmp;
            }
        }
        ++*n_films;
    }

    if (rc == WRONG_FILM_ERR)
        return WRONG_FILM_ERR;

    return ferror(f) != 0;
}

int films_bin_search(film_t sorted_films[], size_t n_films, int field, char *key, size_t *index)
{
    *index = n_films + 1;
    if (field != TITLE && field != NAME && field != YEAR)
        return WRONG_FIELD_ERR;

    int year_key;
    if (field == YEAR && sscanf(key, "%d", &year_key) != 1)
        return WRONG_YEAR_KEY_ERR;

    size_t left_i = 0;
    size_t right_i = n_films - 1;
    size_t cur_i;

    while (left_i <= right_i)
    {
        cur_i = left_i + (right_i - left_i) / 2;
        if ((field == TITLE && strcmp(sorted_films[cur_i].title, key) > 0) ||
            (field == NAME && strcmp(sorted_films[cur_i].name, key) > 0) ||
            (field == YEAR && sorted_films[cur_i].year > year_key))
        {
            if (cur_i == 0)
                return 0;
            right_i = cur_i - 1;
        }
        else if ((field == TITLE && strcmp(sorted_films[cur_i].title, key) < 0) ||
            (field == NAME && strcmp(sorted_films[cur_i].name, key) < 0) ||
            (field == YEAR && sorted_films[cur_i].year < year_key))
            left_i = cur_i + 1;
        else
        {
            *index = cur_i;
            break;
        }
    }

    return 0;
}

void films_print(film_t films[], size_t n_films)
{
    for (size_t i = 0; i < n_films; ++i)
        film_print(&films[i]);
}

void film_print(film_t *film)
{
    printf("%s\n%s\n%d\n", film->title, film->name, film->year);
}
