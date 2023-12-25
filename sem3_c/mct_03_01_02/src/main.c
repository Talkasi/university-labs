#define _GNU_SOURCE
#include "matrix.h"
#include <stdio.h>

int main()
{
    int rc;
    matrix_t m;

    if (scanf("%zi", &m.n_rows) != 1 || m.n_rows <= 0)
        return SCAN_ERR;

    if (scanf("%zi", &m.n_cols) != 1 || m.n_cols <= 0)
        return SCAN_ERR;

    if ((rc = alloc_matrix(&m)))
        return rc;

    if ((rc = scan_matrix(&m)))
    {
        free_matrix(&m);
        return rc;
    }

    if ((rc = del_min_el_col(&m)))
    {
        free_matrix(&m);
        return rc;
    }

    if (!(m.n_rows == 0 && m.n_cols == 0))
    {
        print_matrix(&m);
        free_matrix(&m);
    }

    return 0;
}