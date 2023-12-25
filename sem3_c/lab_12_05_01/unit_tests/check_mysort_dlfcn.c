#include "check_mysort.h"
#include <check.h>
#include <dlfcn.h>
#include <stdio.h>

enum err
{
    MALLOC_ERR = 101,
    ZERO_ARR_ERR = 102,
    WRONG_POINTERS,
    NOT_ENOUGH_MEMORY
};

#define LIB_PATH "src/libarr_dyn.so"

typedef int (*fn_cmp_ints_t)(const void *, const void *);
typedef void (*fn_mysort_t)(void *, size_t, size_t, int (*compare)(const void *, const void *));
static int load_lib_func(void *hlib, void **func, char *func_name);

START_TEST(one_elem_arr)
{
    int arr[] = {1};
    size_t arr_len = sizeof(arr) / sizeof(arr[0]);
    int ans_arr[] = {1};

    void *hlib = dlopen(LIB_PATH, RTLD_NOW);
    ck_assert_int_eq(hlib != NULL, 1);

    fn_cmp_ints_t cmp_ints;
    fn_mysort_t mysort;
    ck_assert_int_eq(load_lib_func(hlib, (void **)&cmp_ints, "cmp_ints"), 0);
    ck_assert_int_eq(load_lib_func(hlib, (void **)&mysort, "mysort"), 0);

    mysort(arr, arr_len, sizeof(int), cmp_ints);
    ck_assert_int_eq(arr[0], ans_arr[0]);
    dlclose(hlib);
}
END_TEST

START_TEST(sorted_arr)
{
    int arr[] = {1, 2, 3};
    size_t arr_len = sizeof(arr) / sizeof(arr[0]);
    int ans_arr[] = {1, 2, 3};

    void *hlib = dlopen(LIB_PATH, RTLD_NOW);
    ck_assert_int_eq(hlib != NULL, 1);

    fn_cmp_ints_t cmp_ints;
    fn_mysort_t mysort;
    ck_assert_int_eq(load_lib_func(hlib, (void **)&cmp_ints, "cmp_ints"), 0);
    ck_assert_int_eq(load_lib_func(hlib, (void **)&mysort, "mysort"), 0);

    mysort(arr, arr_len, sizeof(int), cmp_ints);

    for (size_t i = 0; i < arr_len; ++i)
        ck_assert_int_eq(arr[i], ans_arr[i]);
    dlclose(hlib);
}
END_TEST

START_TEST(one_move_from_end_to_sort)
{
    int arr[] = {1, 2, 3, -12};
    size_t arr_len = sizeof(arr) / sizeof(arr[0]);
    int ans_arr[] = {-12, 1, 2, 3};

    void *hlib = dlopen(LIB_PATH, RTLD_NOW);
    ck_assert_int_eq(hlib != NULL, 1);

    fn_cmp_ints_t cmp_ints;
    fn_mysort_t mysort;
    ck_assert_int_eq(load_lib_func(hlib, (void **)&cmp_ints, "cmp_ints"), 0);
    ck_assert_int_eq(load_lib_func(hlib, (void **)&mysort, "mysort"), 0);

    mysort(arr, arr_len, sizeof(int), cmp_ints);

    for (size_t i = 0; i < arr_len; ++i)
        ck_assert_int_eq(arr[i], ans_arr[i]);
    dlclose(hlib);
}
END_TEST

START_TEST(one_move_from_start_to_sort)
{
    int arr[] = {1012, 1, 2, 3};
    size_t arr_len = sizeof(arr) / sizeof(arr[0]);
    int ans_arr[] = {1, 2, 3, 1012};

    void *hlib = dlopen(LIB_PATH, RTLD_NOW);
    ck_assert_int_eq(hlib != NULL, 1);

    fn_cmp_ints_t cmp_ints;
    fn_mysort_t mysort;
    ck_assert_int_eq(load_lib_func(hlib, (void **)&cmp_ints, "cmp_ints"), 0);
    ck_assert_int_eq(load_lib_func(hlib, (void **)&mysort, "mysort"), 0);

    mysort(arr, arr_len, sizeof(int), cmp_ints);

    for (size_t i = 0; i < arr_len; ++i)
        ck_assert_int_eq(arr[i], ans_arr[i]);
    dlclose(hlib);
}
END_TEST

START_TEST(one_move_from_middle_to_sort)
{
    int arr[] = {1, 2, 1, 3, 5};
    size_t arr_len = sizeof(arr) / sizeof(arr[0]);
    int ans_arr[] = {1, 1, 2, 3, 5};

    void *hlib = dlopen(LIB_PATH, RTLD_NOW);
    ck_assert_int_eq(hlib != NULL, 1);

    fn_cmp_ints_t cmp_ints;
    fn_mysort_t mysort;
    ck_assert_int_eq(load_lib_func(hlib, (void **)&cmp_ints, "cmp_ints"), 0);
    ck_assert_int_eq(load_lib_func(hlib, (void **)&mysort, "mysort"), 0);

    mysort(arr, arr_len, sizeof(int), cmp_ints);

    for (size_t i = 0; i < arr_len; ++i)
        ck_assert_int_eq(arr[i], ans_arr[i]);
    dlclose(hlib);
}
END_TEST

START_TEST(unsorted_arr)
{
    int arr[] = {1, 2376, 12, -231, -23, 293, 123123, 3};
    size_t arr_len = sizeof(arr) / sizeof(arr[0]);
    int ans_arr[] = {-231, -23, 1, 3, 12, 293, 2376, 123123};

    void *hlib = dlopen(LIB_PATH, RTLD_NOW);
    ck_assert_int_eq(hlib != NULL, 1);

    fn_cmp_ints_t cmp_ints;
    fn_mysort_t mysort;
    ck_assert_int_eq(load_lib_func(hlib, (void **)&cmp_ints, "cmp_ints"), 0);
    ck_assert_int_eq(load_lib_func(hlib, (void **)&mysort, "mysort"), 0);

    mysort(arr, arr_len, sizeof(int), cmp_ints);

    for (size_t i = 0; i < arr_len; ++i)
        ck_assert_int_eq(arr[i], ans_arr[i]);
    dlclose(hlib);
}
END_TEST

Suite *mysort_suite()
{
    Suite *s;
    TCase *tc_core;

    s = suite_create("mysort");

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

static int load_lib_func(void *hlib, void **func, char *func_name)
{
    *func = dlsym(hlib, func_name);
    if (*func == NULL)
    {
        printf("%s\n", dlerror());
        return 1;
    }

    return 0;
}
