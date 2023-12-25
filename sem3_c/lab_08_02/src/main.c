#include "matrix.h"
#include <stdio.h>
#define _GNU_SOURCE

int init_matrix(matrix_t *m);

int main()
{
    int rc;
    matrix_t matrix1;
    matrix_t matrix2;

    printf("Working with the first matrix.\n");
    if ((rc = init_matrix(&matrix1)))
        return rc;

    printf("Working with the second matrix.\n");
    if ((rc = init_matrix(&matrix2)))
    {
        free_matrix(&matrix1);
        return rc;
    }

    if ((rc = matrix_to_square_by_del(&matrix1)))
    {
        free_matrix(&matrix1);
        free_matrix(&matrix2);
        return rc;
    }

    if ((rc = matrix_to_square_by_del(&matrix2)))
    {
        free_matrix(&matrix1);
        free_matrix(&matrix2);
        return rc;
    }

    if (matrix1.n_rows > matrix2.n_rows)
    {
        if ((rc = matrix_to_square_by_add(&matrix2, matrix1.n_rows)))
        {
            free_matrix(&matrix1);
            free_matrix(&matrix2);
            return rc;
        }
    }
    else if (matrix1.n_rows < matrix2.n_rows)
        if ((rc = matrix_to_square_by_add(&matrix1, matrix2.n_rows)))
        {
            free_matrix(&matrix1);
            free_matrix(&matrix2);
            return rc;
        }

    ssize_t pow1;
    ssize_t pow2;

    printf("Enter power of the first matrix: ");
    if (scanf("%zd", &pow1) != 1 || pow1 < 0)
    {
        free_matrix(&matrix1);
        free_matrix(&matrix2);
        return SCAN_ERR;
    }

    printf("Enter power of the second matrix: ");
    if (scanf("%zd", &pow2) != 1 || pow2 < 0)
    {
        free_matrix(&matrix1);
        free_matrix(&matrix2);
        return SCAN_ERR;
    }

    if ((rc = raise_square_matrix(&matrix1, (size_t)pow1)))
    {
        free_matrix(&matrix1);
        free_matrix(&matrix2);
        return rc;
    }

    if ((rc = raise_square_matrix(&matrix2, (size_t)pow2)))
    {
        free_matrix(&matrix1);
        free_matrix(&matrix2);
        return rc;
    }

    matrix_t res_matrix;
    pre_init_matrix(&res_matrix);
    if ((rc = mul_square_matrixes(&matrix1, &matrix2, &res_matrix)))
    {
        free_matrix(&matrix1);
        free_matrix(&matrix2);
        free_matrix(&res_matrix);
        return rc;
    }

    printf("Result matrix:\n");
    print_matrix(&res_matrix);

    free_matrix(&matrix1);
    free_matrix(&matrix2);
    free_matrix(&res_matrix);

    return 0;
}

int init_matrix(matrix_t *m)
{
    ssize_t n_rows;
    ssize_t n_cols;

    printf("Enter number of rows of the matrix: ");
    if (scanf("%zd", &n_rows) != 1 || n_rows <= 0)
        return SCAN_ERR;

    printf("Enter number of cols of the matrix: ");
    if (scanf("%zd", &n_cols) != 1 || n_cols <= 0)
        return SCAN_ERR;

    if (alloc_matrix(m, (size_t)n_rows, (size_t)n_cols))
        return MALLOC_ERR;

    printf("Enter elements of the matrix:\n");
    if (scan_matrix(m))
    {
        free_matrix(m);
        return SCAN_ERR;
    }

    return 0;
}
