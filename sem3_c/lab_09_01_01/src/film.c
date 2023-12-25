#include "film.h"
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#define _GNU_SOURCE

int alloc_films(film_t **films, size_t n_films)
{
    *films = calloc(n_films, sizeof(film_t));
    if (!*films)
        return ALLOC_ERR;

    return 0;
}

int realloc_films(film_t **films, size_t old_n_films, size_t new_n_films)
{
    void *tmp = realloc(*films, new_n_films * sizeof(film_t));
    if (!tmp)
    {
        free_films(*films, old_n_films);
        return REALLOC_ERR;
    }
    *films = tmp;

    return 0;
}

void free_films(film_t *films, size_t n_films)
{
    for (size_t i = 0; i < n_films; ++i)
        free_film(&films[i]);

    free(films);
}

void free_film(film_t *film)
{
    free(film->title);
    free(film->name);

    film->title = NULL;
    film->name = NULL;
}

int read_line(FILE *f, char **s, size_t *s_len)
{
    *s = NULL;

    if (getline(s, s_len, f) == -1)
    {
        free(*s);
        *s = NULL;
        *s_len = 0;
        return READ_ERR;
    }

    char *ps = *s;
    *s_len = strlen(ps);

    if (ps[*s_len - 1] == '\n')
        ps[--*s_len] = '\0';

    for (size_t i = 0; i < *s_len; ++i)
        if (!isspace(ps[i]))
            return 0;

    return READ_ERR;
}

int film_read(FILE *f, film_t *film)
{
    size_t tmp;

    if (read_line(f, &film->title, &tmp))
        return NO_FILM_ERR;

    if (read_line(f, &film->name, &tmp))
    {
        free(film->title);
        film->title = NULL;
        return WRONG_FILM_ERR;
    }

    if (fscanf(f, "%d\n", &film->year) != 1 || film->year < 0)
    {
        free(film->title);
        free(film->name);

        film->title = NULL;
        film->name = NULL;
        return WRONG_FILM_ERR;
    }

    return 0;
}

void film_rshift(film_t *films, size_t i_left, size_t i_right)
{
    for (size_t j = i_right; j > i_left; --j)
        films[j] = films[j - 1];
}

int fread_data_to_arr(FILE *f, film_t **films, size_t *n_films, field_args_t field)
{
    *n_films = 0;

    size_t cur_films_len = FILMS_CAPACITY;
    if (alloc_films(films, cur_films_len))
        return ALLOC_ERR;

    rewind(f);
    if (film_read(f, films[0]) != 0)
    {
        free_films(*films, cur_films_len);
        return READ_ERR;
    }

    ++*n_films;
    int rc;
    film_t tmp;
    while ((rc = film_read(f, &tmp)) == 0)
    {
        if (*n_films + 1 > cur_films_len)
        {
            cur_films_len += FILMS_CAPACITY;
            if (realloc_films(films, cur_films_len - FILMS_CAPACITY, cur_films_len))
            {
                *n_films = 0;
                return REALLOC_ERR;
            }
        }

        film_t *films_arr = *films;
        for (size_t i = *n_films; i > 0; --i)
        {
            if ((field == TITLE && strcmp(tmp.title, films_arr[i - 1].title) >= 0) ||
                (field == NAME && strcmp(tmp.name, films_arr[i - 1].name) >= 0) ||
                (field == YEAR && tmp.year >= films_arr[i - 1].year))
            {
                film_rshift(*films, i, *n_films);
                memcpy(&films_arr[i], &tmp, sizeof(film_t));
                break;
            }
            else if (i == 1)
            {
                film_rshift(*films, 0, *n_films);
                memcpy(&films_arr[0], &tmp, sizeof(film_t));
            }
        }
        ++*n_films;
    }

    if (rc == WRONG_FILM_ERR)
    {
        free_films(*films, cur_films_len);
        *n_films = 0;
        return WRONG_FILM_ERR;
    }

    if (ferror(f))
    {
        free_films(*films, cur_films_len);
        *n_films = 0;
        return READ_ERR;
    }

    if (realloc_films(films, cur_films_len, *n_films))
    {
        *n_films = 0;
        return REALLOC_ERR;
    }

    return 0;
}

int films_bin_search(film_t *sorted_films, size_t n_films, field_args_t field, char *key, size_t *index)
{
    *index = n_films + 1;

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

void films_print(film_t *films, size_t n_films)
{
    for (size_t i = 0; i < n_films; ++i)
        film_print(&films[i]);
}

void film_print(film_t *film)
{
    printf("%s\n%s\n%d\n", film->title, film->name, film->year);
}
