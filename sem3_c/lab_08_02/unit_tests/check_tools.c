#include "check_tools.h"
#include <stdlib.h>
#include <string.h>

void ck_cpy_matrix(matrix_t *dst, ck_matrix_t src)
{
    for (size_t i = 0; i < dst->n_rows; ++i)
        memcpy(dst->data[i], src[i], dst->n_cols * sizeof(ck_type));
}

void ck_cmp_matrix(matrix_t *m1, ck_matrix_t m2)
{
    for (size_t i = 0; i < m1->n_rows; ++i)
        for (size_t j = 0; j < m1->n_cols; ++j)
            ck_assert_int_eq(m1->data[i][j], m2[i][j]);
}

void ck_cpy_ck_matrix(ck_matrix_t dst, ck_matrix_t src)
{
    for (size_t i = 0; i < MAX_N_ROWS; ++i)
        memcpy(dst[i], src[i], MAX_N_COLS * sizeof(ck_type));
}

void ck_cmp_ck_matrix(ck_matrix_t m1, ck_matrix_t m2)
{
    for (size_t i = 0; i < MAX_N_COLS; ++i)
        for (size_t j = 0; j < MAX_N_ROWS; ++j)
            ck_assert_int_eq(m1[i][j], m2[i][j]);
}
