#include "check_tools.h"
#include "matrix.h"
#include <check.h>
#include <stdlib.h>

START_TEST(square_matrix)
{
    matrix_t m;
    m.n_rows = 3;
    m.n_cols = 3;

    ck_matrix_t matrix_els = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}};

    ck_matrix_t matrix_els_cp;
    ck_cpy_ck_matrix(matrix_els_cp, matrix_els);

    alloc_matrix(&m, m.n_rows, m.n_cols);
    ck_cpy_matrix(&m, matrix_els);

    ck_assert_int_eq(matrix_to_square_by_del(&m), 0);
    ck_assert_mem_eq(&m.n_rows, &m.n_cols, sizeof(size_t));

    ck_cmp_ck_matrix(matrix_els_cp, matrix_els);
    ck_cmp_matrix(&m, matrix_els);

    free_matrix(&m);
}
END_TEST

START_TEST(eq_matrix_elems_del_col)
{
    matrix_t m;
    m.n_rows = 2;
    m.n_cols = 3;
    size_t needed_size = 2;

    ck_matrix_t matrix_els = {{0, 0, 0}, {0, 0, 0}};
    ck_matrix_t matrix_res = {{0, 0}, {0, 0}};

    ck_matrix_t matrix_els_cp;
    ck_cpy_ck_matrix(matrix_els_cp, matrix_els);

    alloc_matrix(&m, m.n_rows, m.n_cols);
    ck_cpy_matrix(&m, matrix_els);

    ck_assert_int_eq(matrix_to_square_by_del(&m), 0);
    ck_assert_mem_eq(&m.n_rows, &m.n_cols, sizeof(size_t));
    ck_assert_mem_eq(&m.n_rows, &needed_size, sizeof(size_t));

    ck_cmp_ck_matrix(matrix_els_cp, matrix_els);
    ck_cmp_matrix(&m, matrix_res);

    free_matrix(&m);
}
END_TEST

START_TEST(eq_matrix_elems_del_row)
{
    matrix_t m;
    m.n_rows = 3;
    m.n_cols = 2;
    size_t needed_size = 2;

    ck_matrix_t matrix_els = {{0, 0}, {0, 0}, {0, 0}};
    ck_matrix_t matrix_res = {{0, 0}, {0, 0}};

    ck_matrix_t matrix_els_cp;
    ck_cpy_ck_matrix(matrix_els_cp, matrix_els);

    alloc_matrix(&m, m.n_rows, m.n_cols);
    ck_cpy_matrix(&m, matrix_els);

    ck_assert_int_eq(matrix_to_square_by_del(&m), 0);
    ck_assert_mem_eq(&m.n_rows, &m.n_cols, sizeof(size_t));
    ck_assert_mem_eq(&m.n_rows, &needed_size, sizeof(size_t));

    ck_cmp_ck_matrix(matrix_els_cp, matrix_els);
    ck_cmp_matrix(&m, matrix_res);

    free_matrix(&m);
}
END_TEST

START_TEST(del_rows_at_start)
{
    matrix_t m;
    m.n_rows = 3;
    m.n_cols = 2;
    size_t needed_size = 2;

    ck_matrix_t matrix_els = {{5342, -123123}, {223, 0}, {-20, 20}};
    ck_matrix_t matrix_res = {{223, 0}, {-20, 20}};

    ck_matrix_t matrix_els_cp;
    ck_cpy_ck_matrix(matrix_els_cp, matrix_els);

    alloc_matrix(&m, m.n_rows, m.n_cols);
    ck_cpy_matrix(&m, matrix_els);

    ck_assert_int_eq(matrix_to_square_by_del(&m), 0);
    ck_assert_mem_eq(&m.n_rows, &m.n_cols, sizeof(size_t));
    ck_assert_mem_eq(&m.n_rows, &needed_size, sizeof(size_t));

    ck_cmp_ck_matrix(matrix_els_cp, matrix_els);
    ck_cmp_matrix(&m, matrix_res);

    free_matrix(&m);
}
END_TEST

START_TEST(del_cols_at_start)
{
    matrix_t m;
    m.n_rows = 2;
    m.n_cols = 3;
    size_t needed_size = 2;

    ck_matrix_t matrix_els = {{1231323, 1231, 123}, {123, -1232, 0}};
    ck_matrix_t matrix_res = {{1231, 123}, {-1232, 0}};

    ck_matrix_t matrix_els_cp;
    ck_cpy_ck_matrix(matrix_els_cp, matrix_els);

    alloc_matrix(&m, m.n_rows, m.n_cols);
    ck_cpy_matrix(&m, matrix_els);

    ck_assert_int_eq(matrix_to_square_by_del(&m), 0);
    ck_assert_mem_eq(&m.n_rows, &m.n_cols, sizeof(size_t));
    ck_assert_mem_eq(&m.n_rows, &needed_size, sizeof(size_t));

    ck_cmp_ck_matrix(matrix_els_cp, matrix_els);
    ck_cmp_matrix(&m, matrix_res);

    free_matrix(&m);
}
END_TEST

START_TEST(del_rows_in_the_middle)
{
    matrix_t m;
    m.n_rows = 7;
    m.n_cols = 2;
    size_t needed_size = 2;

    ck_matrix_t matrix_els = {{0, 0}, {1, 2}, {3, 4}, {4, 3}, {5, 6}, {-23, -23}, {-23, 0}};
    ck_matrix_t matrix_res = {{0, 0}, {-23, -23}};

    ck_matrix_t matrix_els_cp;
    ck_cpy_ck_matrix(matrix_els_cp, matrix_els);

    alloc_matrix(&m, m.n_rows, m.n_cols);
    ck_cpy_matrix(&m, matrix_els);

    ck_assert_int_eq(matrix_to_square_by_del(&m), 0);
    ck_assert_mem_eq(&m.n_rows, &m.n_cols, sizeof(size_t));
    ck_assert_mem_eq(&m.n_rows, &needed_size, sizeof(size_t));

    ck_cmp_ck_matrix(matrix_els_cp, matrix_els);
    ck_cmp_matrix(&m, matrix_res);

    free_matrix(&m);
}
END_TEST

START_TEST(del_cols_in_the_middle)
{
    matrix_t m;
    m.n_rows = 3;
    m.n_cols = 5;
    size_t needed_size = 3;

    ck_matrix_t matrix_els = {{1, 1, 1, 1, 1}, {1, 23, -12, 12, 1}, {1, 2, 34, 34, 1}};
    ck_matrix_t matrix_res = {{1, 1, 1}, {1, 23, 1}, {1, 2, 1}};

    ck_matrix_t matrix_els_cp;
    ck_cpy_ck_matrix(matrix_els_cp, matrix_els);

    alloc_matrix(&m, m.n_rows, m.n_cols);
    ck_cpy_matrix(&m, matrix_els);

    ck_assert_int_eq(matrix_to_square_by_del(&m), 0);
    ck_assert_mem_eq(&m.n_rows, &m.n_cols, sizeof(size_t));
    ck_assert_mem_eq(&m.n_rows, &needed_size, sizeof(size_t));

    ck_cmp_ck_matrix(matrix_els_cp, matrix_els);
    ck_cmp_matrix(&m, matrix_res);

    free_matrix(&m);
}
END_TEST

START_TEST(del_rows_in_the_end)
{
    matrix_t m;
    m.n_rows = 5;
    m.n_cols = 2;
    size_t needed_size = 2;

    ck_matrix_t matrix_els = {{-123123123, 15}, {13, 13}, {112312, 0}, {-123, 349}, {1323, 123}};
    ck_matrix_t matrix_res = {{-123123123, 15}, {13, 13}};

    ck_matrix_t matrix_els_cp;
    ck_cpy_ck_matrix(matrix_els_cp, matrix_els);

    alloc_matrix(&m, m.n_rows, m.n_cols);
    ck_cpy_matrix(&m, matrix_els);

    ck_assert_int_eq(matrix_to_square_by_del(&m), 0);
    ck_assert_mem_eq(&m.n_rows, &m.n_cols, sizeof(size_t));
    ck_assert_mem_eq(&m.n_rows, &needed_size, sizeof(size_t));

    ck_cmp_ck_matrix(matrix_els_cp, matrix_els);
    ck_cmp_matrix(&m, matrix_res);

    free_matrix(&m);
}
END_TEST

START_TEST(del_cols_in_the_end)
{
    matrix_t m;
    m.n_rows = 2;
    m.n_cols = 5;
    size_t needed_size = 2;

    ck_matrix_t matrix_els = {{1, -264, 3, 4, 5234}, {-1, -234, -3, -4234, -5}};
    ck_matrix_t matrix_res = {{1, -264}, {-1, -234}};

    ck_matrix_t matrix_els_cp;
    ck_cpy_ck_matrix(matrix_els_cp, matrix_els);

    alloc_matrix(&m, m.n_rows, m.n_cols);
    ck_cpy_matrix(&m, matrix_els);

    ck_assert_int_eq(matrix_to_square_by_del(&m), 0);
    ck_assert_mem_eq(&m.n_rows, &m.n_cols, sizeof(size_t));
    ck_assert_mem_eq(&m.n_rows, &needed_size, sizeof(size_t));

    ck_cmp_ck_matrix(matrix_els_cp, matrix_els);
    ck_cmp_matrix(&m, matrix_res);

    free_matrix(&m);
}
END_TEST

Suite *square_by_del_suite()
{
    Suite *s;
    TCase *tc_core;

    s = suite_create("Square by del");

    tc_core = tcase_create("Square_by_del_core");

    tcase_add_test(tc_core, square_matrix);
    tcase_add_test(tc_core, eq_matrix_elems_del_col);
    tcase_add_test(tc_core, eq_matrix_elems_del_row);
    tcase_add_test(tc_core, del_rows_at_start);
    tcase_add_test(tc_core, del_cols_at_start);
    tcase_add_test(tc_core, del_rows_in_the_middle);
    tcase_add_test(tc_core, del_cols_in_the_middle);
    tcase_add_test(tc_core, del_rows_in_the_end);
    tcase_add_test(tc_core, del_cols_in_the_end);

    suite_add_tcase(s, tc_core);

    return s;
}
