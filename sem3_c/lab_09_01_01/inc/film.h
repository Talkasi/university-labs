#ifndef FILM_H
#define FILM_H
#include <stdio.h>

#define FILMS_CAPACITY 3

enum film_errs
{
    WRONG_FIELD_ERR = -20,
    NO_FILM_ERR,
    WRONG_FILM_ERR,
    WRONG_YEAR_KEY_ERR,
    ALLOC_ERR,
    REALLOC_ERR,
    READ_ERR,
};

enum field_args
{
    INVALID,
    TITLE,
    NAME,
    YEAR
};

struct film_info
{
    char *title;
    char *name;
    int year;
};

typedef struct film_info film_t;
typedef enum field_args field_args_t;

int alloc_films(film_t **films, size_t n_films);
int realloc_films(film_t **films, size_t old_n_films, size_t new_n_films);
void free_films(film_t *films, size_t n_films);
void free_film(film_t *film);

int fread_data_to_arr(FILE *f, film_t **films, size_t *n_films, field_args_t field);
int films_bin_search(film_t *sorted_films, size_t n_films, field_args_t field, char *key, size_t *index);

int film_read(FILE *f, film_t *film);
void film_print(film_t *film);
void films_print(film_t *films, size_t n_films);

#endif
