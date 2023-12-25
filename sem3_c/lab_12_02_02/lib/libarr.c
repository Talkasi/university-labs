#include "libarr.h"
#include <stdlib.h>

int init_arr_by_fib(int *arr, size_t n)
{
    if (arr == NULL)
        return NO_ARR;

    if (n > 0)
        arr[0] = 1;

    if (n > 1)
        arr[1] = 1;

    for (size_t i = 2; i < n; ++i)
        arr[i] = arr[i - 1] + arr[i - 2];

    return 0;
}

static int first_unique_el(int *arr, size_t index)
{
    for (size_t i = 0; i < index; ++i)
        if (arr[i] == arr[index])
            return 0;

    return 1;
}

size_t init_by_first_unique(int *src, size_t src_n, int *dst, size_t dst_n, size_t *n_initialized)
{
    size_t more_els_needed = 0;
    *n_initialized = 0;
    for (size_t i = 0; i < src_n; ++i)
        if (first_unique_el(src, i))
        {
            if (*n_initialized < dst_n)
            {
                dst[*n_initialized] = src[i];
                ++*n_initialized;
            }
            else
                ++more_els_needed;
        }

    if (more_els_needed == 0)
        return 0;

    return dst_n + more_els_needed;
}
