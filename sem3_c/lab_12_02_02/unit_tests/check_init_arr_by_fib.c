#include "libarr.h"
#include <check.h>
#include <stdlib.h>

START_TEST(array_is_null)
{
    size_t arr_len = 1;
    int *arr = NULL;

    ck_assert_int_eq(init_arr_by_fib(arr, arr_len), NO_ARR);
}
END_TEST

START_TEST(array_len_is_zero)
{
    size_t arr_len = 0;
    int arr[1] = {};

    ck_assert_int_eq(init_arr_by_fib(arr, arr_len), 0);

    ck_assert_int_eq(arr[0], 0);
}
END_TEST

START_TEST(one_elem_in_the_array)
{
    size_t arr_len = 1;
    int arr[arr_len];

    ck_assert_int_eq(init_arr_by_fib(arr, arr_len), 0);

    ck_assert_int_eq(arr[0], 1);
}
END_TEST

START_TEST(two_elems_in_the_array)
{
    size_t arr_len = 2;
    int arr[arr_len];

    ck_assert_int_eq(init_arr_by_fib(arr, arr_len), 0);

    ck_assert_int_eq(arr[0], 1);
    ck_assert_int_eq(arr[1], 1);
}
END_TEST

START_TEST(three_elems_in_the_array)
{
    size_t arr_len = 3;
    int arr[arr_len];

    ck_assert_int_eq(init_arr_by_fib(arr, arr_len), 0);

    ck_assert_int_eq(arr[0], 1);
    ck_assert_int_eq(arr[1], 1);
    ck_assert_int_eq(arr[2], 2);
}
END_TEST

START_TEST(ten_elems_in_the_array)
{
    size_t arr_len = 10;
    int arr[arr_len];

    ck_assert_int_eq(init_arr_by_fib(arr, arr_len), 0);

    ck_assert_int_eq(arr[0], 1);
    ck_assert_int_eq(arr[1], 1);

    for (size_t i = 2; i < arr_len; ++i)
        ck_assert_int_eq(arr[i], arr[i - 1] + arr[i - 2]);
}
END_TEST

START_TEST(hundred_elems_in_the_array)
{
    size_t arr_len = 100;
    int arr[arr_len];

    ck_assert_int_eq(init_arr_by_fib(arr, arr_len), 0);

    ck_assert_int_eq(arr[0], 1);
    ck_assert_int_eq(arr[1], 1);

    for (size_t i = 2; i < arr_len; ++i)
        ck_assert_int_eq(arr[i], arr[i - 1] + arr[i - 2]);
}
END_TEST

Suite *init_arr_by_fib_suite()
{
    Suite *s;
    TCase *tc_core;

    s = suite_create("Init arr by fib");

    tc_core = tcase_create("Init_arr_by_fib_core");

    tcase_add_test(tc_core, array_is_null);
    tcase_add_test(tc_core, array_len_is_zero);
    tcase_add_test(tc_core, one_elem_in_the_array);
    tcase_add_test(tc_core, two_elems_in_the_array);
    tcase_add_test(tc_core, three_elems_in_the_array);
    tcase_add_test(tc_core, ten_elems_in_the_array);
    tcase_add_test(tc_core, hundred_elems_in_the_array);

    suite_add_tcase(s, tc_core);

    return s;
}
