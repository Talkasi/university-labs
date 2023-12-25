#include "my_arr.h"
#include <stdlib.h>
#include <string.h>

int key(const int *pb_src, const int *pe_src, int **pb_dst, int **pe_dst)
{
    if (pb_src >= pe_src)
        return WRONG_POINTERS;

    int sum = 0, sum_tmp;
    for (const int *cur = pb_src; cur < pe_src; ++cur)
        sum += *cur;

    sum_tmp = sum;
    long n_needed = 0;
    for (const int *cur = pb_src; cur < pe_src - 1; ++cur)
    {
        sum -= *cur;
        if (*cur > sum)
            ++n_needed;
    }

    if (n_needed == 0)
        return ZERO_ARR_ERR;

    if (*pe_dst - *pb_dst < n_needed)
        return NOT_ENOUGH_MEMORY;

    long i = 0;
    for (const int *cur = pb_src; cur < pe_src - 1; ++cur)
    {
        sum_tmp -= *cur;
        if (*cur > sum_tmp)
            *(*pb_dst + i++) = *cur;
    }

    *pe_dst = *pb_dst + i;
    return 0;
}

void mysort(void *base, size_t nmemb, size_t size, int (*compare)(const void *, const void *))
{
    char key[size];
    char *runner;
    char *ps = base;
    char *pb = (char *)base + nmemb * size;

    for (char *cur_memb = ps + size; cur_memb < pb; cur_memb = cur_memb + size)
    {
        memcpy(key, cur_memb, size);
        runner = cur_memb - size;

        while (runner >= ps && compare(runner, key) > 0)
        {
            memcpy(runner + size, runner, size);
            runner -= size;
        }
        memcpy(runner + size, key, size);
    }
}

int cmp_ints(const void *v1, const void *v2)
{
    const int *a = v1;
    const int *b = v2;
    return *a - *b;
}

long fcount_data(FILE *f)
{
    long c = 0;
    int num;
    rewind(f);
    while (fscanf(f, "%d", &num) == 1)
        ++c;

    if (feof(f))
        return c;
    return -1;
}

int fread_data(FILE *f, int *arr_s, int *arr_e)
{
    rewind(f);

    for (long i = 0; arr_s + i < arr_e; ++i)
        if (fscanf(f, "%d", arr_s + i) != 1)
            return -1;

    return 0;
}

int fwrite_data(FILE *f, int *arr_s, int *arr_e)
{
    rewind(f);

    for (int *cur = arr_s; cur < arr_e; ++cur)
        if (fprintf(f, "%d ", *cur) < 0)
            return 0;

    return 1;
}
