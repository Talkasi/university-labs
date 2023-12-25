#ifndef ARR_H
#define ARR_H
#include <stdio.h>

#define ALLOC_ERR 101
#define REALLOC_ERR 102
#define SCAN_ERR 103

struct arr
{
    int *data;
    ssize_t n_els;
};

typedef struct arr arr_t;

int alloc_arr(arr_t *a);
void free_arr(arr_t *a);
int del_mod_three(arr_t *a);

void print_arr(arr_t *a);
int scan_arr(arr_t *a);

#endif