#ifndef MY_ARR_H
#define MY_ARR_H
#include <stddef.h>

#define MALLOC_ERR 101
#define ZERO_ARR_ERR 102
#define WRONG_POINTERS 103

int cmp_ints(const void *v1, const void *v2);
int key(const int *pb_src, const int *pe_src, int **pb_dst, int **pe_dst);
void mysort(void *base, size_t nmemb, size_t size, int (*compare)(const void *, const void *));

#endif