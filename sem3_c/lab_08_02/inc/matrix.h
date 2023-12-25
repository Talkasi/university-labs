#ifndef MATRIX_H
#define MATRIX_H
#include <stdio.h>

#define SCAN_ERR 100
#define MALLOC_ERR 101
#define REALLOC_ERR 102
#define WRONG_POS_ERR 103

struct matrix
{
    int **data;
    size_t n_rows;
    size_t n_cols;
};

typedef struct matrix matrix_t;

int alloc_matrix(matrix_t *m, size_t n_rows, size_t n_cols);
void free_matrix(matrix_t *m);

int scan_matrix(matrix_t *m);
void print_matrix(matrix_t *m);

int matrix_to_square_by_del(matrix_t *m);
int matrix_to_square_by_add(matrix_t *m, size_t needed_size);
int raise_square_matrix(matrix_t *m, size_t pow);
int mul_square_matrixes(matrix_t *m1, matrix_t *m2, matrix_t *res);
void pre_init_matrix(matrix_t *m);

#endif