#include "matrix.h"
#include <stdio.h>
#include <stdlib.h>

int alloc_matrix(matrix_t *m)
{
    void *tmp = calloc(sizeof(int *), m->n_rows);
    if (!tmp)
        return ALLOC_ERR;

    m->data = tmp;
    for (ssize_t i = 0; i < m->n_rows; ++i)
    {
        m->data[i] = malloc(sizeof(int) * m->n_cols);
        if (!m->data[i])
        {
            free_matrix(m);
            return ALLOC_ERR;
        }
    }

    return 0;
}

void free_matrix(matrix_t *m)
{
    for (ssize_t i = 0; i < m->n_rows; ++i)
        free(m->data[i]);

    free(m->data);
}

int del_min_el_col(matrix_t *m)
{
    int min_el = m->data[0][0];
    ssize_t min_el_col = 0;

    for (ssize_t i = 0; i < m->n_rows; ++i)
        for (ssize_t j = 0; j < m->n_cols; ++j)
            if (m->data[i][j] < min_el)
            {
                min_el = m->data[i][j];
                min_el_col = j;
            }

    for (ssize_t i = 0; i < m->n_rows; ++i)
    {
        for (ssize_t j = min_el_col; j < m->n_cols - 1; ++j)
            m->data[i][j] = m->data[i][j + 1];

        m->data[i] = realloc(m->data[i], sizeof(int) * (m->n_cols - 1));
        if (m->data[i] == NULL && m->n_cols - 1 != 0)
        {
            free_matrix(m);
            return REALLOC_ERR;
        }
    }

    --m->n_cols;
    return 0;
}

int scan_matrix(matrix_t *m)
{
    for (ssize_t i = 0; i < m->n_rows; ++i)
        for (ssize_t j = 0; j < m->n_cols; ++j)
            if (scanf("%d", &m->data[i][j]) != 1)
                return SCAN_ERR;
    return 0;
}

void print_matrix(matrix_t *m)
{
    for (ssize_t i = 0; i < m->n_rows; ++i)
    {
        for (ssize_t j = 0; j < m->n_cols; ++j)
            printf("%d ", m->data[i][j]);
        printf("\n");
    }
}
