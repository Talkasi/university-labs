#define _GNU_SOURCE
#include "arr.h"
#include <stdio.h>

int main()
{
    int rc;
    arr_t a;

    if (scanf("%zi", &a.n_els) != 1 || a.n_els <= 0)
        return SCAN_ERR;

    if ((rc = alloc_arr(&a)))
        return rc;

    if ((rc = scan_arr(&a)))
    {
        free_arr(&a);
        return rc;
    }

    if ((rc = del_mod_three(&a)))
    {
        free_arr(&a);
        return rc;
    }

    if (a.n_els > 0)
    {
        print_arr(&a);
        free_arr(&a);
    }

    return 0;
}