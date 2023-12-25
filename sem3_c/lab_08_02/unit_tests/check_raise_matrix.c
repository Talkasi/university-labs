#include "check_tools.h"
#include "matrix.h"
#include <check.h>
#include <stdlib.h>

START_TEST(matrix_with_one_elem_to_0_pow)
{
    matrix_t m;
    m.n_rows = 1;
    m.n_cols = 1;

    ck_matrix_t matrix_els = {{0}};
    ck_matrix_t matrix_res = {{1}};

    size_t power = 0;

    ck_matrix_t matrix_els_cp;
    ck_cpy_ck_matrix(matrix_els_cp, matrix_els);

    alloc_matrix(&m, m.n_rows, m.n_cols);
    ck_cpy_matrix(&m, matrix_els);

    ck_assert_int_eq(raise_square_matrix(&m, power), 0);
    ck_assert_mem_eq(&m.n_rows, &m.n_cols, sizeof(size_t));

    ck_cmp_matrix(&m, matrix_res);
    ck_cmp_ck_matrix(matrix_els_cp, matrix_els);

    free_matrix(&m);
}
END_TEST

START_TEST(matrix_with_one_elem_to_5_pow)
{
    matrix_t m;
    m.n_rows = 1;
    m.n_cols = 1;

    ck_matrix_t matrix_els = {{2}};
    ck_matrix_t matrix_res = {{32}};

    size_t power = 5;

    ck_matrix_t matrix_els_cp;
    ck_cpy_ck_matrix(matrix_els_cp, matrix_els);

    alloc_matrix(&m, m.n_rows, m.n_cols);
    ck_cpy_matrix(&m, matrix_els);

    ck_assert_int_eq(raise_square_matrix(&m, power), 0);
    ck_assert_mem_eq(&m.n_rows, &m.n_cols, sizeof(size_t));

    ck_cmp_matrix(&m, matrix_res);
    ck_cmp_ck_matrix(matrix_els_cp, matrix_els);

    free_matrix(&m);
}
END_TEST

START_TEST(power_0)
{
    matrix_t m;
    m.n_rows = 3;
    m.n_cols = 3;

    ck_matrix_t matrix_els = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}};
    ck_matrix_t matrix_res = {{1, 0, 0}, {0, 1, 0}, {0, 0, 1}};

    size_t power = 0;

    ck_matrix_t matrix_els_cp;
    ck_cpy_ck_matrix(matrix_els_cp, matrix_els);

    alloc_matrix(&m, m.n_rows, m.n_cols);
    ck_cpy_matrix(&m, matrix_els);

    ck_assert_int_eq(raise_square_matrix(&m, power), 0);
    ck_assert_mem_eq(&m.n_rows, &m.n_cols, sizeof(size_t));

    ck_cmp_matrix(&m, matrix_res);
    ck_cmp_ck_matrix(matrix_els_cp, matrix_els);

    free_matrix(&m);
}
END_TEST

START_TEST(power_1)
{
    matrix_t m;
    m.n_rows = 5;
    m.n_cols = 5;

    ck_matrix_t matrix_els = {{1, 2, 3, 4, 5}, {1, 2, 3, 4, 5}, {1, 2, 3, 4, 5}, {1, 2, 3, 4, 5}, {1, 2, 3, 4, 5}};
    ck_matrix_t matrix_res = {{1, 2, 3, 4, 5}, {1, 2, 3, 4, 5}, {1, 2, 3, 4, 5}, {1, 2, 3, 4, 5}, {1, 2, 3, 4, 5}};

    size_t power = 1;

    ck_matrix_t matrix_els_cp;
    ck_cpy_ck_matrix(matrix_els_cp, matrix_els);

    alloc_matrix(&m, m.n_rows, m.n_cols);
    ck_cpy_matrix(&m, matrix_els);

    ck_assert_int_eq(raise_square_matrix(&m, power), 0);
    ck_assert_mem_eq(&m.n_rows, &m.n_cols, sizeof(size_t));

    ck_cmp_matrix(&m, matrix_res);
    ck_cmp_ck_matrix(matrix_els_cp, matrix_els);

    free_matrix(&m);
}
END_TEST

START_TEST(power_2)
{
    matrix_t m;
    m.n_rows = 5;
    m.n_cols = 5;

    ck_matrix_t matrix_els = {{1, 2, 3, 4, 5}, {1, 2, 3, 4, 5}, {1, 2, 3, 4, 5}, {1, 2, 3, 4, 5}, {1, 2, 3, 4, 5}};
    ck_matrix_t matrix_res = {
        {15, 30, 45, 60, 75}, {15, 30, 45, 60, 75}, {15, 30, 45, 60, 75}, {15, 30, 45, 60, 75}, {15, 30, 45, 60, 75}};

    size_t power = 2;

    ck_matrix_t matrix_els_cp;
    ck_cpy_ck_matrix(matrix_els_cp, matrix_els);

    alloc_matrix(&m, m.n_rows, m.n_cols);
    ck_cpy_matrix(&m, matrix_els);

    ck_assert_int_eq(raise_square_matrix(&m, power), 0);
    ck_assert_mem_eq(&m.n_rows, &m.n_cols, sizeof(size_t));

    ck_cmp_matrix(&m, matrix_res);
    ck_cmp_ck_matrix(matrix_els_cp, matrix_els);

    free_matrix(&m);
}
END_TEST

START_TEST(power_3)
{
    matrix_t m;
    m.n_rows = 3;
    m.n_cols = 3;

    ck_matrix_t matrix_els = {{1, 2, 3}, {3, 2, 1}, {2, 1, 3}};
    ck_matrix_t matrix_res = {{68, 58, 90}, {72, 58, 86}, {70, 56, 90}};

    size_t power = 3;

    ck_matrix_t matrix_els_cp;
    ck_cpy_ck_matrix(matrix_els_cp, matrix_els);

    alloc_matrix(&m, m.n_rows, m.n_cols);
    ck_cpy_matrix(&m, matrix_els);

    ck_assert_int_eq(raise_square_matrix(&m, power), 0);
    ck_assert_mem_eq(&m.n_rows, &m.n_cols, sizeof(size_t));

    ck_cmp_matrix(&m, matrix_res);
    ck_cmp_ck_matrix(matrix_els_cp, matrix_els);

    free_matrix(&m);
}
END_TEST

START_TEST(power_4)
{
    matrix_t m;
    m.n_rows = 3;
    m.n_cols = 3;

    ck_matrix_t matrix_els = {{10, 9, 8}, {7, 6, 5}, {4, 3, 2}};
    ck_matrix_t matrix_res = {{69930, 60372, 50814}, {47412, 40932, 34452}, {24894, 21492, 18090}};

    size_t power = 4;

    ck_matrix_t matrix_els_cp;
    ck_cpy_ck_matrix(matrix_els_cp, matrix_els);

    alloc_matrix(&m, m.n_rows, m.n_cols);
    ck_cpy_matrix(&m, matrix_els);

    ck_assert_int_eq(raise_square_matrix(&m, power), 0);
    ck_assert_mem_eq(&m.n_rows, &m.n_cols, sizeof(size_t));

    ck_cmp_matrix(&m, matrix_res);
    ck_cmp_ck_matrix(matrix_els_cp, matrix_els);

    free_matrix(&m);
}
END_TEST

START_TEST(power_5)
{
    matrix_t m;
    m.n_rows = 3;
    m.n_cols = 3;

    ck_matrix_t matrix_els = {{1, 2, 3}, {10, 9, 8}, {0, -12, 1}};
    ck_matrix_t matrix_res = {{-34359, 5554, -39233}, {-158350, -61775, -157700}, {124080, 190020, 85585}};

    size_t power = 5;

    ck_matrix_t matrix_els_cp;
    ck_cpy_ck_matrix(matrix_els_cp, matrix_els);

    alloc_matrix(&m, m.n_rows, m.n_cols);
    ck_cpy_matrix(&m, matrix_els);

    ck_assert_int_eq(raise_square_matrix(&m, power), 0);
    ck_assert_mem_eq(&m.n_rows, &m.n_cols, sizeof(size_t));

    ck_cmp_matrix(&m, matrix_res);
    ck_cmp_ck_matrix(matrix_els_cp, matrix_els);

    free_matrix(&m);
}
END_TEST

START_TEST(big_matrix_power_5)
{
    matrix_t m;
    m.n_rows = 5;
    m.n_cols = 5;

    ck_matrix_t matrix_els = {{1, 2, 3, 4, 5}, {1, 2, 3, 4, 5}, {1, 2, 3, 4, 5}, {1, 2, 3, 4, 5}, {1, 2, 3, 4, 5}};
    ck_matrix_t matrix_res = {{50625, 101250, 151875, 202500, 253125},
                              {50625, 101250, 151875, 202500, 253125},
                              {50625, 101250, 151875, 202500, 253125},
                              {50625, 101250, 151875, 202500, 253125},
                              {50625, 101250, 151875, 202500, 253125}};

    size_t power = 5;

    ck_matrix_t matrix_els_cp;
    ck_cpy_ck_matrix(matrix_els_cp, matrix_els);

    alloc_matrix(&m, m.n_rows, m.n_cols);
    ck_cpy_matrix(&m, matrix_els);

    ck_assert_int_eq(raise_square_matrix(&m, power), 0);
    ck_assert_mem_eq(&m.n_rows, &m.n_cols, sizeof(size_t));

    ck_cmp_matrix(&m, matrix_res);
    ck_cmp_ck_matrix(matrix_els_cp, matrix_els);

    free_matrix(&m);
}
END_TEST

START_TEST(power_6)
{
    matrix_t m;
    m.n_rows = 4;
    m.n_cols = 4;

    ck_matrix_t matrix_els = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16}};
    ck_matrix_t matrix_res = {{149395360, 169176640, 188957920, 208739200},
                              {345173152, 390877248, 436581344, 482285440},
                              {540950944, 612577856, 684204768, 755831680},
                              {736728736, 834278464, 931828192, 1029377920}};

    size_t power = 6;

    ck_matrix_t matrix_els_cp;
    ck_cpy_ck_matrix(matrix_els_cp, matrix_els);

    alloc_matrix(&m, m.n_rows, m.n_cols);
    ck_cpy_matrix(&m, matrix_els);

    ck_assert_int_eq(raise_square_matrix(&m, power), 0);
    ck_assert_mem_eq(&m.n_rows, &m.n_cols, sizeof(size_t));

    ck_cmp_matrix(&m, matrix_res);
    ck_cmp_ck_matrix(matrix_els_cp, matrix_els);

    free_matrix(&m);
}
END_TEST

START_TEST(power_7)
{
    matrix_t m;
    m.n_rows = 2;
    m.n_cols = 2;

    ck_matrix_t matrix_els = {{0, -1}, {-2, 1}};
    ck_matrix_t matrix_res = {{42, -43}, {-86, 85}};

    size_t power = 7;

    ck_matrix_t matrix_els_cp;
    ck_cpy_ck_matrix(matrix_els_cp, matrix_els);

    alloc_matrix(&m, m.n_rows, m.n_cols);
    ck_cpy_matrix(&m, matrix_els);

    ck_assert_int_eq(raise_square_matrix(&m, power), 0);
    ck_assert_mem_eq(&m.n_rows, &m.n_cols, sizeof(size_t));

    ck_cmp_matrix(&m, matrix_res);
    ck_cmp_ck_matrix(matrix_els_cp, matrix_els);

    free_matrix(&m);
}
END_TEST

Suite *raise_matrix_suite()
{
    Suite *s;
    TCase *tc_core;

    s = suite_create("Raise matrix");

    tc_core = tcase_create("raise_matrix_core");

    tcase_add_test(tc_core, matrix_with_one_elem_to_0_pow);
    tcase_add_test(tc_core, matrix_with_one_elem_to_5_pow);
    tcase_add_test(tc_core, power_0);
    tcase_add_test(tc_core, power_1);
    tcase_add_test(tc_core, power_2);
    tcase_add_test(tc_core, power_3);
    tcase_add_test(tc_core, power_4);
    tcase_add_test(tc_core, power_5);
    tcase_add_test(tc_core, big_matrix_power_5);
    tcase_add_test(tc_core, power_6);
    tcase_add_test(tc_core, power_7);

    suite_add_tcase(s, tc_core);

    return s;
}
