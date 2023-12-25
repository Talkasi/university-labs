#include "check_mysort.h"
#include "my_arr.h"
#include <check.h>

START_TEST(one_elem_arr)
{
    int arr[] = {1};
    size_t arr_len = sizeof(arr) / sizeof(arr[0]);
    int ans_arr[] = {1};

    mysort(arr, arr_len, sizeof(int), cmp_ints);
    ck_assert_int_eq(arr[0], ans_arr[0]);
}
END_TEST

START_TEST(sorted_arr)
{
    int arr[] = {1, 2, 3};
    size_t arr_len = sizeof(arr) / sizeof(arr[0]);
    int ans_arr[] = {1, 2, 3};

    mysort(arr, arr_len, sizeof(int), cmp_ints);

    for (size_t i = 0; i < arr_len; ++i)
        ck_assert_int_eq(arr[i], ans_arr[i]);
}
END_TEST

START_TEST(one_move_from_end_to_sort)
{
    int arr[] = {1, 2, 3, -12};
    size_t arr_len = sizeof(arr) / sizeof(arr[0]);
    int ans_arr[] = {-12, 1, 2, 3};

    mysort(arr, arr_len, sizeof(int), cmp_ints);

    for (size_t i = 0; i < arr_len; ++i)
        ck_assert_int_eq(arr[i], ans_arr[i]);
}
END_TEST

START_TEST(one_move_from_start_to_sort)
{
    int arr[] = {1012, 1, 2, 3};
    size_t arr_len = sizeof(arr) / sizeof(arr[0]);
    int ans_arr[] = {1, 2, 3, 1012};

    mysort(arr, arr_len, sizeof(int), cmp_ints);

    for (size_t i = 0; i < arr_len; ++i)
        ck_assert_int_eq(arr[i], ans_arr[i]);
}
END_TEST

START_TEST(one_move_from_middle_to_sort)
{
    int arr[] = {1, 2, 1, 3, 5};
    size_t arr_len = sizeof(arr) / sizeof(arr[0]);
    int ans_arr[] = {1, 1, 2, 3, 5};

    mysort(arr, arr_len, sizeof(int), cmp_ints);

    for (size_t i = 0; i < arr_len; ++i)
        ck_assert_int_eq(arr[i], ans_arr[i]);
}
END_TEST

START_TEST(unsorted_arr)
{
    int arr[] = {1, 2376, 12, -231, -23, 293, 123123, 3};
    size_t arr_len = sizeof(arr) / sizeof(arr[0]);
    int ans_arr[] = {-231, -23, 1, 3, 12, 293, 2376, 123123};

    mysort(arr, arr_len, sizeof(int), cmp_ints);

    for (size_t i = 0; i < arr_len; ++i)
        ck_assert_int_eq(arr[i], ans_arr[i]);
}
END_TEST

Suite *mysort_suite()
{
    Suite *s;
    TCase *tc_core;

    s = suite_create("Mysort");

    tc_core = tcase_create("Mysort_core");

    tcase_add_test(tc_core, one_elem_arr);
    tcase_add_test(tc_core, sorted_arr);
    tcase_add_test(tc_core, one_move_from_middle_to_sort);
    tcase_add_test(tc_core, one_move_from_start_to_sort);
    tcase_add_test(tc_core, one_move_from_end_to_sort);
    tcase_add_test(tc_core, unsorted_arr);
    suite_add_tcase(s, tc_core);

    return s;
}