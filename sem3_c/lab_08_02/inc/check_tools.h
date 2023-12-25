#ifndef CHECK_TOOLS_H
#define CHECK_TOOLS_H
#include "matrix.h"
#include <check.h>

#define MAX_N_ROWS 20
#define MAX_N_COLS 20

typedef int ck_type;
typedef ck_type ck_matrix_t[MAX_N_ROWS][MAX_N_COLS];

void ck_cpy_matrix(matrix_t *dst, ck_matrix_t src);
void ck_cmp_matrix(matrix_t *m1, ck_matrix_t m2);

void ck_cpy_ck_matrix(ck_matrix_t dst, ck_matrix_t src);
void ck_cmp_ck_matrix(ck_matrix_t m1, ck_matrix_t m2);

#endif