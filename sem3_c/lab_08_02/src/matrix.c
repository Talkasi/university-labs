#include "matrix.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void pre_init_matrix(matrix_t *m)
{
    m->data = NULL;
    m->n_rows = 0;
    m->n_cols = 0;
}

int alloc_matrix(matrix_t *m, size_t n_rows, size_t n_cols)
{
    m->n_rows = n_rows;
    m->n_cols = n_cols;

    m->data = calloc(m->n_rows, sizeof(int *));
    if (!m->data)
        return MALLOC_ERR;

    for (size_t i = 0; i < m->n_rows; ++i)
    {
        m->data[i] = malloc(m->n_cols * sizeof(int));
        if (!m->data[i])
        {
            for (size_t j = i; i < m->n_rows; ++i)
                m->data[j] = NULL;

            free_matrix(m);
            return MALLOC_ERR;
        }
    }

    return 0;
}

int realloc_cols(matrix_t *m)
{
    for (size_t i = 0; i < m->n_rows; ++i)
    {
        m->data[i] = realloc(m->data[i], m->n_cols * sizeof(int));
        if (!m->data[i])
        {
            free_matrix(m);
            return REALLOC_ERR;
        }
    }

    return 0;
}

int realloc_rows(matrix_t *m, size_t new_n_rows)
{
    void *tmp = realloc(m->data, sizeof(int *) * new_n_rows);
    if (!tmp)
    {
        free_matrix(m);
        return REALLOC_ERR;
    }
    m->data = tmp;

    for (size_t i = m->n_rows; i < new_n_rows; ++i)
        m->data[i] = NULL;

    for (size_t i = m->n_rows; i < new_n_rows; ++i)
    {
        m->data[i] = malloc(m->n_cols * sizeof(int));
        if (!m->data[i])
        {
            free_matrix(m);
            return MALLOC_ERR;
        }
    }

    m->n_rows = new_n_rows;
    return 0;
}

int realloc_matrix(matrix_t *m, size_t new_n_rows)
{
    void *tmp = realloc(m->data, sizeof(int *) * new_n_rows);
    if (!tmp)
    {
        free_matrix(m);
        return REALLOC_ERR;
    }
    m->data = tmp;

    for (size_t i = m->n_rows; i < new_n_rows; ++i)
        m->data[i] = NULL;

    for (size_t i = 0; i < new_n_rows; ++i)
    {
        m->data[i] = realloc(m->data[i], m->n_cols * sizeof(int));
        if (!m->data[i])
        {
            free_matrix(m);
            return REALLOC_ERR;
        }
    }

    m->n_rows = new_n_rows;
    return 0;
}

void free_matrix(matrix_t *m)
{
    for (size_t i = 0; i < m->n_rows; ++i)
        free(m->data[i]);

    free(m->data);
    pre_init_matrix(m);
}

int find_max_el(matrix_t *m, size_t *max_el_row, size_t *max_el_col)
{
    int max_el = m->data[0][0];
    size_t row = 0;
    size_t col = 0;

    for (size_t i = 0; i < m->n_rows; ++i)
        for (size_t j = 0; j < m->n_cols; ++j)
            if (max_el <= m->data[i][j])
            {
                max_el = m->data[i][j];
                row = i;
                col = j;
            }

    if (max_el_row)
        *max_el_row = row;

    if (max_el_col)
        *max_el_col = col;

    return max_el;
}

int matrix_del_rows(matrix_t *m)
{
    size_t r_to_del;

    while (m->n_rows > m->n_cols)
    {
        find_max_el(m, &r_to_del, NULL);

        free(m->data[r_to_del]);
        for (size_t i = r_to_del; i < m->n_rows - 1; ++i)
            m->data[i] = m->data[i + 1];

        --m->n_rows;
    }

    if (realloc_rows(m, m->n_rows))
        return REALLOC_ERR;

    return 0;
}

int matrix_del_cols(matrix_t *m)
{
    size_t c_to_del;

    while (m->n_cols > m->n_rows)
    {
        find_max_el(m, NULL, &c_to_del);

        for (size_t i = 0; i < m->n_rows; ++i)
            for (size_t j = c_to_del; j < m->n_cols - 1; ++j)
                m->data[i][j] = m->data[i][j + 1];

        --m->n_cols;
    }

    if (realloc_cols(m))
        return REALLOC_ERR;

    return 0;
}

int matrix_to_square_by_del(matrix_t *m)
{
    int rc;
    if (m->n_rows > m->n_cols)
    {
        if ((rc = matrix_del_rows(m)))
            return rc;
    }
    else if (m->n_rows < m->n_cols)
        if ((rc = matrix_del_cols(m)))
            return rc;

    return 0;
}

int matrix_add_rows(matrix_t *m, size_t needed_row_n)
{
    int rc;
    size_t prev_n_rows = m->n_rows;
    if ((rc = realloc_rows(m, needed_row_n)))
        return rc;

    for (size_t res_i = prev_n_rows; res_i < m->n_rows; ++res_i)
    {
        for (size_t j = 0; j < m->n_cols; ++j)
        {
            m->data[res_i][j] = 0;
            for (size_t i = 0; i < res_i; ++i)
                m->data[res_i][j] += m->data[i][j];
            m->data[res_i][j] = (int)floor((double)m->data[res_i][j] / (double)res_i);
        }
    }

    return 0;
}

int matrix_add_cols(matrix_t *m, size_t needed_col_n)
{
    size_t prev_n_cols = m->n_cols;
    m->n_cols = needed_col_n;
    if (realloc_cols(m))
        return REALLOC_ERR;

    for (size_t res_j = prev_n_cols; res_j < m->n_cols; ++res_j)
    {
        for (size_t i = 0; i < m->n_rows; ++i)
        {
            m->data[i][res_j] = m->data[i][0];
            for (size_t j = 1; j < res_j; ++j)
                if (m->data[i][res_j] > m->data[i][j])
                    m->data[i][res_j] = m->data[i][j];
        }
    }

    return 0;
}

int matrix_to_square_by_add(matrix_t *m, size_t needed_size)
{
    int rc;
    if ((rc = matrix_add_rows(m, needed_size)))
        return rc;

    if ((rc = matrix_add_cols(m, needed_size)))
        return rc;

    return 0;
}

void cp_matrix(matrix_t *dst, matrix_t *src)
{
    for (size_t i = 0; i < src->n_rows; ++i)
        memcpy(dst->data[i], src->data[i], sizeof(int) * src->n_cols);
}

void fill_as_identity(matrix_t *m)
{
    for (size_t i = 0; i < m->n_rows; ++i)
        for (size_t j = 0; j < m->n_cols; ++j)
            m->data[i][j] = (i == j);
}

int mul_square_matrixes(matrix_t *m1, matrix_t *m2, matrix_t *res)
{
    int rc;
    res->n_cols = m2->n_cols;
    if ((rc = realloc_matrix(res, m1->n_rows)))
        return rc;

    for (size_t i = 0; i < m1->n_rows; ++i)
        for (size_t j = 0; j < m2->n_cols; ++j)
        {
            res->data[i][j] = 0;
            for (size_t k = 0; k < m1->n_cols; ++k)
                res->data[i][j] += m1->data[i][k] * m2->data[k][j];
        }

    return 0;
}

int raise_square_matrix(matrix_t *m, size_t pow)
{
    int rc;

    if (pow == 0)
    {
        fill_as_identity(m);
        return 0;
    }

    if (pow == 1)
        return 0;

    matrix_t tmp;
    if ((rc = alloc_matrix(&tmp, m->n_rows, m->n_cols)))
        return rc;

    matrix_t start_m;
    if ((rc = alloc_matrix(&start_m, m->n_rows, m->n_cols)))
    {
        free_matrix(&tmp);
        return rc;
    }
    cp_matrix(&start_m, m);

    size_t i_pow;
    for (i_pow = 1; i_pow * 2 <= pow; i_pow *= 2)
    {
        if ((rc = mul_square_matrixes(m, m, &tmp)))
        {
            free_matrix(&tmp);
            free_matrix(&start_m);
            return rc;
        }

        cp_matrix(m, &tmp);
    }

    for (size_t cur_pow = 0; cur_pow < pow - i_pow; ++cur_pow)
    {
        if ((rc = mul_square_matrixes(m, &start_m, &tmp)))
        {
            free_matrix(&tmp);
            free_matrix(&start_m);
            return rc;
        }

        cp_matrix(m, &tmp);
    }

    free_matrix(&tmp);
    free_matrix(&start_m);

    return 0;
}

int scan_matrix(matrix_t *m)
{
    for (size_t i = 0; i < m->n_rows; ++i)
        for (size_t j = 0; j < m->n_cols; ++j)
            if (scanf("%d", &m->data[i][j]) != 1)
                return SCAN_ERR;

    return 0;
}

void print_matrix(matrix_t *m)
{
    for (size_t i = 0; i < m->n_rows; ++i)
    {
        for (size_t j = 0; j < m->n_cols; ++j)
            printf("%8d ", m->data[i][j]);

        printf("\n");
    }
}
