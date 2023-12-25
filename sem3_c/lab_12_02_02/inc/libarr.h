#ifndef MY_ARR_H
#define MY_ARR_H
#include <stdio.h>

enum err
{
    NO_ARR = -101,
    NOT_ENOUGH_MEMORY = -102,
};

int init_arr_by_fib(int *arr, size_t n);
size_t init_by_first_unique(int *src, size_t src_n, int *dst, size_t dst_n, size_t *n_initialized);

#endif