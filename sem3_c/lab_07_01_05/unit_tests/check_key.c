#include "my_arr.h"
#include <check.h>
#include <stdlib.h>

START_TEST(eq_wrong_pointers)
{
    int arr[] = {1, 2, 3};
    int *ps, *pe;

    ck_assert_int_eq(key(arr, arr, &ps, &pe), WRONG_POINTERS);
}
END_TEST

START_TEST(neq_wrong_pointers)
{
    int arr[] = {1, 2, 3};
    size_t arr_len = sizeof(arr) / sizeof(arr[0]);
    int *ps, *pe;

    ck_assert_int_eq(key(arr + arr_len, arr, &ps, &pe), WRONG_POINTERS);
}
END_TEST

START_TEST(one_element_arr)
{
    int arr[] = {1};
    int *ps, *pe;

    ck_assert_int_eq(key(arr, arr + 1, &ps, &pe), ZERO_ARR_ERR);
}
END_TEST

START_TEST(no_elements_after_filtering)
{
    int arr[] = {1, 2, 3, 4, 5};
    size_t arr_len = sizeof(arr) / sizeof(arr[0]);
    int *ps, *pe;

    ck_assert_int_eq(key(arr, arr + arr_len, &ps, &pe), ZERO_ARR_ERR);
}
END_TEST

START_TEST(each_before_the_last_remains)
{
    int arr[] = {101, 20, 3, 0, -12};
    int ans_arr[] = {101, 20, 3, 0};
    size_t arr_len = sizeof(arr) / sizeof(arr[0]);
    size_t ans_arr_len = sizeof(ans_arr) / sizeof(ans_arr[0]);
    int *ps, *pe;

    ck_assert_int_eq(key(arr, arr + arr_len, &ps, &pe), 0);
    ck_assert_int_eq(pe - ps, ans_arr_len);

    for (size_t i = 0; i < ans_arr_len; ++i)
        ck_assert_int_eq(ans_arr[i], ps[i]);

    free(ps);
}
END_TEST

START_TEST(only_first_remains)
{
    int arr[] = {101, 0, 3, 0, 12};
    int ans_arr[] = {101};
    size_t arr_len = sizeof(arr) / sizeof(arr[0]);
    size_t ans_arr_len = sizeof(ans_arr) / sizeof(ans_arr[0]);
    int *ps, *pe;

    ck_assert_int_eq(key(arr, arr + arr_len, &ps, &pe), 0);
    ck_assert_int_eq(pe - ps, ans_arr_len);

    for (size_t i = 0; i < ans_arr_len; ++i)
        ck_assert_int_eq(ans_arr[i], ps[i]);

    free(ps);
}
END_TEST

START_TEST(only_one_before_the_last_remains)
{
    int arr[] = {10, -444, 700, 700, 12};
    int ans_arr[] = {700};
    size_t arr_len = sizeof(arr) / sizeof(arr[0]);
    size_t ans_arr_len = sizeof(ans_arr) / sizeof(ans_arr[0]);
    int *ps, *pe;

    ck_assert_int_eq(key(arr, arr + arr_len, &ps, &pe), 0);
    ck_assert_int_eq(pe - ps, ans_arr_len);
    ck_assert_int_eq(ans_arr[0], ps[0]);

    free(ps);
}
END_TEST

START_TEST(several_in_middle_remain)
{
    int arr[] = {10, 4444, 101, -70, 12};
    int ans_arr[] = {4444, 101};
    size_t arr_len = sizeof(arr) / sizeof(arr[0]);
    size_t ans_arr_len = sizeof(ans_arr) / sizeof(ans_arr[0]);
    int *ps, *pe;

    ck_assert_int_eq(key(arr, arr + arr_len, &ps, &pe), 0);
    ck_assert_int_eq(pe - ps, ans_arr_len);

    for (size_t i = 0; i < ans_arr_len; ++i)
        ck_assert_int_eq(ans_arr[i], ps[i]);

    free(ps);
}
END_TEST

Suite *key_suite()
{
    Suite *s;
    TCase *tc_core;

    s = suite_create("Key");

    tc_core = tcase_create("Key_core");

    /* Neg testing */
    tcase_add_test(tc_core, eq_wrong_pointers);
    tcase_add_test(tc_core, neq_wrong_pointers);
    tcase_add_test(tc_core, one_element_arr);
    tcase_add_test(tc_core, no_elements_after_filtering);

    /* Pos testing */
    tcase_add_test(tc_core, each_before_the_last_remains);
    tcase_add_test(tc_core, only_first_remains);
    tcase_add_test(tc_core, several_in_middle_remain);
    tcase_add_test(tc_core, only_one_before_the_last_remains);

    suite_add_tcase(s, tc_core);

    return s;
}