#ifndef MATRIX_H
#define MATRIX_H
#include <stdio.h>

#define ALLOC_ERR 101
#define REALLOC_ERR 102
#define SCAN_ERR 103

struct matrix
{
    int **data;
    ssize_t n_rows;
    ssize_t n_cols;
};

typedef struct matrix matrix_t;

int del_min_el_col(matrix_t *m);
void free_matrix(matrix_t *m);
int alloc_matrix(matrix_t *m);

int scan_matrix(matrix_t *m);
void print_matrix(matrix_t *m);

#endif