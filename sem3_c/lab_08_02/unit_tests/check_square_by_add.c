#include "check_tools.h"
#include "matrix.h"
#include <check.h>
#include <stdlib.h>

START_TEST(nothing_to_add)
{
    matrix_t m;
    m.n_rows = 3;
    m.n_cols = 3;
    size_t needed_size = 3;

    ck_matrix_t matrix_els = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}};
    ck_matrix_t matrix_res = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}};

    ck_matrix_t matrix_els_cp;
    ck_cpy_ck_matrix(matrix_els_cp, matrix_els);

    alloc_matrix(&m, m.n_rows, m.n_cols);
    ck_cpy_matrix(&m, matrix_els);

    ck_assert_int_eq(matrix_to_square_by_add(&m, needed_size), 0);
    ck_assert_mem_eq(&m.n_rows, &m.n_cols, sizeof(size_t));

    ck_cmp_matrix(&m, matrix_res);
    ck_cmp_ck_matrix(matrix_els_cp, matrix_els);

    free_matrix(&m);
}
END_TEST

START_TEST(add_one_row_and_col_zero)
{
    matrix_t m;
    m.n_rows = 3;
    m.n_cols = 3;
    size_t needed_size = 4;

    ck_matrix_t matrix_els = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}};
    ck_matrix_t matrix_res = {{0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}};

    ck_matrix_t matrix_els_cp;
    ck_cpy_ck_matrix(matrix_els_cp, matrix_els);

    alloc_matrix(&m, m.n_rows, m.n_cols);
    ck_cpy_matrix(&m, matrix_els);

    ck_assert_int_eq(matrix_to_square_by_add(&m, needed_size), 0);
    ck_assert_mem_eq(&m.n_rows, &m.n_cols, sizeof(size_t));

    ck_cmp_matrix(&m, matrix_res);
    ck_cmp_ck_matrix(matrix_els_cp, matrix_els);

    free_matrix(&m);
}
END_TEST

START_TEST(add_one_row_and_col)
{
    matrix_t m;
    m.n_rows = 3;
    m.n_cols = 3;
    size_t needed_size = 4;

    ck_matrix_t matrix_els = {{1, 2, 3}, {3, 2, 1}, {2, 1, 3}};
    ck_matrix_t matrix_res = {{1, 2, 3, 1}, {3, 2, 1, 1}, {2, 1, 3, 1}, {2, 1, 2, 1}};

    ck_matrix_t matrix_els_cp;
    ck_cpy_ck_matrix(matrix_els_cp, matrix_els);

    alloc_matrix(&m, m.n_rows, m.n_cols);
    ck_cpy_matrix(&m, matrix_els);

    ck_assert_int_eq(matrix_to_square_by_add(&m, needed_size), 0);
    ck_assert_mem_eq(&m.n_rows, &m.n_cols, sizeof(size_t));

    ck_cmp_matrix(&m, matrix_res);
    ck_cmp_ck_matrix(matrix_els_cp, matrix_els);

    free_matrix(&m);
}
END_TEST

START_TEST(add_sev_rows_and_cols_zero)
{
    matrix_t m;
    m.n_rows = 2;
    m.n_cols = 2;
    size_t needed_size = 5;

    ck_matrix_t matrix_els = {{0, 0}, {0, 0}};
    ck_matrix_t matrix_res = {{0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}};

    ck_matrix_t matrix_els_cp;
    ck_cpy_ck_matrix(matrix_els_cp, matrix_els);

    alloc_matrix(&m, m.n_rows, m.n_cols);
    ck_cpy_matrix(&m, matrix_els);

    ck_assert_int_eq(matrix_to_square_by_add(&m, needed_size), 0);
    ck_assert_mem_eq(&m.n_rows, &m.n_cols, sizeof(size_t));

    ck_cmp_matrix(&m, matrix_res);
    ck_cmp_ck_matrix(matrix_els_cp, matrix_els);

    free_matrix(&m);
}
END_TEST

START_TEST(add_sev_rows_and_cols)
{
    matrix_t m;
    m.n_rows = 3;
    m.n_cols = 3;
    size_t needed_size = 5;

    ck_matrix_t matrix_els = {{1, 2, 3}, {3, 2, 1}, {2, 1, 3}};
    ck_matrix_t matrix_res = {{1, 2, 3, 1, 1}, {3, 2, 1, 1, 1}, {2, 1, 3, 1, 1}, {2, 1, 2, 1, 1}, {2, 1, 2, 1, 1}};

    ck_matrix_t matrix_els_cp;
    ck_cpy_ck_matrix(matrix_els_cp, matrix_els);

    alloc_matrix(&m, m.n_rows, m.n_cols);
    ck_cpy_matrix(&m, matrix_els);

    ck_assert_int_eq(matrix_to_square_by_add(&m, needed_size), 0);
    ck_assert_mem_eq(&m.n_rows, &m.n_cols, sizeof(size_t));

    ck_cmp_matrix(&m, matrix_res);
    ck_cmp_ck_matrix(matrix_els_cp, matrix_els);

    free_matrix(&m);
}
END_TEST

Suite *square_by_add_suite()
{
    Suite *s;
    TCase *tc_core;

    s = suite_create("Square by add");

    tc_core = tcase_create("Square_by_add_core");

    tcase_add_test(tc_core, nothing_to_add);
    tcase_add_test(tc_core, add_one_row_and_col_zero);
    tcase_add_test(tc_core, add_one_row_and_col);
    tcase_add_test(tc_core, add_sev_rows_and_cols_zero);
    tcase_add_test(tc_core, add_sev_rows_and_cols);

    suite_add_tcase(s, tc_core);

    return s;
}
