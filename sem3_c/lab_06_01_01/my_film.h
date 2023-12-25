#ifndef MY_FILM_H
#define MY_FILM_H
#include <stdio.h>

#define MAX_TITLE_LEN 26
#define MAX_NAME_LEN 26
#define MAX_STR_LEN 256
#define MAX_YEAR_LEN 10

#define TITLE 0
#define NAME 1
#define YEAR 2

#define WRONG_FIELD_ERR -10
#define NO_FILM_ERR -11
#define WRONG_FILM_ERR -12
#define WRONG_YEAR_KEY_ERR -13

struct film_info
{
    char title[MAX_TITLE_LEN];
    char name[MAX_NAME_LEN];
    int year;
};

typedef struct film_info film_t;

int fread_data_to_arr(FILE *f, film_t films[], size_t max_nfilms, size_t *n_films, int field);
int films_bin_search(film_t sorted_films[], size_t n_films, int field, char *key, size_t *index);

int film_read(FILE *f, film_t *films);
void film_print(film_t *film);
void films_print(film_t films[], size_t n_films);

#endif
