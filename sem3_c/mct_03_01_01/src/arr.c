#include "arr.h"
#include <stdio.h>
#include <stdlib.h>

int alloc_arr(arr_t *a)
{
    int *tmp = malloc(sizeof(int) * a->n_els);
    if (!tmp)
        return ALLOC_ERR;

    a->data = tmp;

    return 0;
}

void free_arr(arr_t *a)
{
    free(a->data);
    a->n_els = 0;
}

int del_mod_three(arr_t *a)
{
    ssize_t new_size = 0;
    for (ssize_t i = 0; i < a->n_els; ++i)
        if (a->data[i] % 3 != 0)
            a->data[new_size++] = a->data[i];

    a->n_els = new_size;

    void *tmp = realloc(a->data, sizeof(int) * a->n_els);
    if (tmp == NULL && a->n_els != 0)
        return REALLOC_ERR;

    a->data = tmp;
    return 0;
}

void print_arr(arr_t *a)
{
    for (ssize_t i = 0; i < a->n_els; ++i)
        printf("%d ", a->data[i]);

    printf("\n");
}

int scan_arr(arr_t *a)
{
    for (ssize_t i = 0; i < a->n_els; ++i)
        if (scanf("%d", &a->data[i]) != 1)
            return SCAN_ERR;

    return 0;
}
