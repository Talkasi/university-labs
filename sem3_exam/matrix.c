#include <stdlib.h>

/*
size_t n = 5;
size_t m = 2;
int *mtx = malloc(n * m * sizeof(int));

free(mtx);
*/

void free_mtx_0(int **mtx, size_t n)
{
    for (size_t i = 0; i < n; ++i)
        free(mtx[i]);

    free(mtx);
}

int **alloc_mtx_0(size_t n, size_t m)
{
    int **mtx = calloc(n, sizeof(int *));
    if (!mtx)
        return NULL;

    for (size_t i = 0; i < n; ++i)
    {
        mtx[i] = malloc(m * sizeof(int));
        if (!mtx[i])
        {
            free_mtx_0(mtx, n);
            return NULL;
        }
    }

    return mtx;
}

void free_mtx_1(int **mtx, size_t n)
{
    free(mtx[0]); // !
    free(mtx);
}

int **alloc_mtx_1(size_t n, size_t m)
{
    int **mtx = calloc(n, sizeof(int *));
    if (!mtx)
        return NULL;

    int *ptr = malloc(n * m * sizeof(int));
    if (!ptr)
    {
        free(mtx);
        return NULL;
    }

    // IMPORTANT: m!
    for (size_t i = 0; i < n; ++i)
        mtx[i] = ptr + m * i;

    return mtx;
}

void free_mtx_2(int **mtx, size_t n)
{
    free(mtx);
}

int **alloc_mtx_2(size_t n, size_t m)
{
    int **mtx = malloc(n * m * sizeof(int) + n * sizeof(int *));
    if (!mtx)
        return NULL;

    // IMPORTANT!
    int *ptr = (int *)(mtx + n);
    for (size_t i = 0; i < n; ++i)
        mtx[i] = ptr + i * m;
}
