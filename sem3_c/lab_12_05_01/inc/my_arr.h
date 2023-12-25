#ifndef MY_ARR_H
#define MY_ARR_H
#include <stdio.h>

enum err
{
    MALLOC_ERR = 101,
    ZERO_ARR_ERR = 102,
    WRONG_POINTERS,
    NOT_ENOUGH_MEMORY
};

int cmp_ints(const void *v1, const void *v2);
int key(const int *pb_src, const int *pe_src, int **pb_dst, int **pe_dst);
void mysort(void *base, size_t nmemb, size_t size, int (*compare)(const void *, const void *));

long fcount_data(FILE *f);
int fread_data(FILE *f, int *arr_s, int *arr_e);
int fwrite_data(FILE *f, int *arr_s, int *arr_e);

#endif