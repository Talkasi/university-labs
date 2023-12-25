#include "check_suites.h"
#include "libarr.h"
#include <check.h>
#include <stdlib.h>

START_TEST(one_elem_arr_dst_is_large_enough)
{
    int src[] = {1};
    size_t src_len = sizeof(src) / sizeof(src[0]);

    size_t dst_len = src_len;
    int dst[dst_len];
    size_t dst_n_inited = 0;

    size_t expexted_n = 1;

    ck_assert_int_eq(init_by_first_unique(src, src_len, dst, dst_len, &dst_n_inited), 0);
    ck_assert_mem_eq(&dst_n_inited, &expexted_n, sizeof(size_t));
    ck_assert_int_eq(src[0], dst[0]);
}
END_TEST

START_TEST(one_elem_arr_dst_is_not_large_enough)
{
    int src[] = {1};
    size_t src_len = sizeof(src) / sizeof(src[0]);

    size_t dst_len = 0;
    int *dst = NULL;
    size_t dst_n_inited = 0;

    size_t expexted_n = 1;

    dst_len = init_by_first_unique(src, src_len, dst, dst_len, &dst_n_inited);
    ck_assert_int_eq(dst_n_inited, 0);
    ck_assert_mem_eq(&dst_len, &expexted_n, sizeof(size_t));

    dst = malloc(dst_len * sizeof(int));
    if (dst != NULL)
    {
        ck_assert_int_eq(init_by_first_unique(src, src_len, dst, dst_len, &dst_n_inited), 0);
        ck_assert_mem_eq(&dst_n_inited, &expexted_n, sizeof(size_t));
        ck_assert_int_eq(src[0], dst[0]);
    }
}
END_TEST

START_TEST(same_numbers_in_arr_dst_is_large_enough)
{
    int src[] = {1, 1, 1, 1, 1, 1};
    size_t src_len = sizeof(src) / sizeof(src[0]);

    size_t dst_len = src_len;
    int dst[dst_len];
    size_t dst_n_inited = 0;

    size_t expexted_n = 1;

    ck_assert_int_eq(init_by_first_unique(src, src_len, dst, dst_len, &dst_n_inited), 0);
    ck_assert_mem_eq(&dst_n_inited, &expexted_n, sizeof(size_t));
    for (size_t i = 0; i < dst_n_inited; ++i)
        ck_assert_int_eq(src[i], dst[i]);
}
END_TEST

START_TEST(same_numbers_in_arr_dst_is_not_large_enough)
{
    int src[] = {1, 1, 1, 1, 1, 1, 1};
    size_t src_len = sizeof(src) / sizeof(src[0]);

    size_t dst_len = 0;
    int *dst = NULL;
    size_t dst_n_inited = 0;

    size_t expexted_n = 1;

    dst_len = init_by_first_unique(src, src_len, dst, dst_len, &dst_n_inited);
    ck_assert_int_eq(dst_n_inited, 0);
    ck_assert_mem_eq(&dst_len, &expexted_n, sizeof(size_t));

    dst = malloc(dst_len * sizeof(int));
    if (dst != NULL)
    {
        ck_assert_int_eq(init_by_first_unique(src, src_len, dst, dst_len, &dst_n_inited), 0);
        ck_assert_mem_eq(&dst_n_inited, &expexted_n, sizeof(size_t));
        for (size_t i = 0; i < dst_n_inited; ++i)
            ck_assert_int_eq(src[i], dst[i]);
    }
}
END_TEST

START_TEST(unique_arr_dst_is_large_enough)
{
    int src[] = {1, 2, 3, 5, 7, 6, 456, 2341};
    size_t src_len = sizeof(src) / sizeof(src[0]);

    size_t dst_len = src_len;
    int dst[dst_len];
    size_t dst_n_inited = 0;

    size_t expexted_n = sizeof(src) / sizeof(src[0]);

    ck_assert_int_eq(init_by_first_unique(src, src_len, dst, dst_len, &dst_n_inited), 0);
    ck_assert_mem_eq(&dst_n_inited, &expexted_n, sizeof(size_t));
    for (size_t i = 0; i < dst_n_inited; ++i)
        ck_assert_int_eq(src[i], dst[i]);
}
END_TEST

START_TEST(unique_arr_dst_is_not_large_enough)
{
    int src[] = {1, 2, 3, 5, 7, 6, 456, 2341};
    size_t src_len = sizeof(src) / sizeof(src[0]);

    size_t dst_len = 0;
    int *dst = NULL;
    size_t dst_n_inited = 0;

    size_t expexted_n = src_len;

    dst_len = init_by_first_unique(src, src_len, dst, dst_len, &dst_n_inited);
    ck_assert_int_eq(dst_n_inited, 0);
    ck_assert_mem_eq(&dst_len, &expexted_n, sizeof(size_t));

    dst = malloc(dst_len * sizeof(int));
    if (dst != NULL)
    {
        ck_assert_int_eq(init_by_first_unique(src, src_len, dst, dst_len, &dst_n_inited), 0);
        ck_assert_mem_eq(&dst_n_inited, &expexted_n, sizeof(size_t));
        for (size_t i = 0; i < dst_n_inited; ++i)
            ck_assert_int_eq(src[i], dst[i]);
    }
}
END_TEST

START_TEST(several_numbers_are_unique_dst_is_large_enough)
{
    int src[] = {1, 2, 3, 5, 7, 1, 2, 2341};
    int dst_exp[] = {1, 2, 3, 5, 7, 2341};
    size_t src_len = sizeof(src) / sizeof(src[0]);

    size_t dst_len = src_len;
    int dst[dst_len];
    size_t dst_n_inited = 0;

    size_t expexted_n = sizeof(dst_exp) / sizeof(dst_exp[0]);

    ck_assert_int_eq(init_by_first_unique(src, src_len, dst, dst_len, &dst_n_inited), 0);
    ck_assert_mem_eq(&dst_n_inited, &expexted_n, sizeof(size_t));
    for (size_t i = 0; i < dst_n_inited; ++i)
        ck_assert_int_eq(dst_exp[i], dst[i]);
}
END_TEST

START_TEST(several_numbers_are_unique_dst_is_not_large_enough)
{
    int src[] = {1, 2, 3, 5, 7, 1, 2, 2341};
    int dst_exp[] = {1, 2, 3, 5, 7, 2341};
    size_t src_len = sizeof(src) / sizeof(src[0]);

    size_t dst_len = 0;
    int *dst = NULL;
    size_t dst_n_inited = 0;

    size_t expexted_n = sizeof(dst_exp) / sizeof(dst_exp[0]);

    dst_len = init_by_first_unique(src, src_len, dst, dst_len, &dst_n_inited);
    ck_assert_int_eq(dst_n_inited, 0);
    ck_assert_mem_eq(&dst_len, &expexted_n, sizeof(size_t));

    dst = malloc(dst_len * sizeof(int));
    if (dst != NULL)
    {
        ck_assert_int_eq(init_by_first_unique(src, src_len, dst, dst_len, &dst_n_inited), 0);
        ck_assert_mem_eq(&dst_n_inited, &expexted_n, sizeof(size_t));
        for (size_t i = 0; i < dst_n_inited; ++i)
            ck_assert_int_eq(dst_exp[i], dst[i]);
    }
}
END_TEST

Suite *init_by_first_unique_suite()
{
    Suite *s;
    TCase *tc_core;

    s = suite_create("Init by first unique");

    tc_core = tcase_create("Init by first unique core");

    tcase_add_test(tc_core, one_elem_arr_dst_is_large_enough);
    tcase_add_test(tc_core, one_elem_arr_dst_is_not_large_enough);
    tcase_add_test(tc_core, unique_arr_dst_is_large_enough);
    tcase_add_test(tc_core, unique_arr_dst_is_not_large_enough);
    tcase_add_test(tc_core, same_numbers_in_arr_dst_is_large_enough);
    tcase_add_test(tc_core, same_numbers_in_arr_dst_is_not_large_enough);
    tcase_add_test(tc_core, several_numbers_are_unique_dst_is_large_enough);
    tcase_add_test(tc_core, several_numbers_are_unique_dst_is_not_large_enough);

    suite_add_tcase(s, tc_core);

    return s;
}