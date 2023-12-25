#include "check_assoc_array_suites.h"
#include "associative_array.h"
#include <check.h>


START_TEST(one_elem)
{
    const char *key = "key";
    int num = 1;
    int *nump;

    assoc_array_t arr = assoc_array_create();
    assoc_array_error_t rc;
    if (arr != NULL) {
        rc = assoc_array_insert(arr, key, num);
        ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
        rc = assoc_array_max(arr, &nump);
        ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
        ck_assert_int_eq(num, *nump);
        assoc_array_destroy(&arr);
    }
}
END_TEST

START_TEST(two_elems_first_max)
{
    const char *key1 = "key2";
    int num1 = 1;

    const char *key2 = "key1";
    int num2 = 2;

    int *nump;

    assoc_array_t arr = assoc_array_create();
    assoc_array_error_t rc;
    if (arr != NULL) {
        rc = assoc_array_insert(arr, key1, num1);
        ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
        rc = assoc_array_insert(arr, key2, num2);
        ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
        rc = assoc_array_max(arr, &nump);
        ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
        ck_assert_int_eq(num1, *nump);
        assoc_array_destroy(&arr);
    }
}
END_TEST

START_TEST(two_elems_second_max)
{
    const char *key1 = "key1";
    int num1 = 1;

    const char *key2 = "key2";
    int num2 = 2;

    int *nump;

    assoc_array_t arr = assoc_array_create();
    assoc_array_error_t rc;
    if (arr != NULL) {
        rc = assoc_array_insert(arr, key1, num1);
        ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
        rc = assoc_array_insert(arr, key2, num2);
        ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
        rc = assoc_array_max(arr, &nump);
        ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
        ck_assert_int_eq(num2, *nump);
        assoc_array_destroy(&arr);
    }
}
END_TEST


START_TEST(three_elems_first_max)
{
    const char *key1 = "key3";
    int num1 = 1;

    const char *key2 = "key2";
    int num2 = 2;

    const char *key3 = "key1";
    int num3 = 3;

    int *nump;

    assoc_array_t arr = assoc_array_create();
    assoc_array_error_t rc;
    if (arr != NULL) {
        rc = assoc_array_insert(arr, key1, num1);
        ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
        rc = assoc_array_insert(arr, key2, num2);
        ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
        rc = assoc_array_insert(arr, key3, num3);
        ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
        rc = assoc_array_max(arr, &nump);
        ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
        ck_assert_int_eq(num1, *nump);

        assoc_array_destroy(&arr);
    }
}
END_TEST

START_TEST(three_elems_second_max)
{
    const char *key1 = "key1";
    int num1 = 1;

    const char *key2 = "key2";
    int num2 = 2;

    const char *key3 = "key0";
    int num3 = 3;

    int *nump;

    assoc_array_t arr = assoc_array_create();
    assoc_array_error_t rc;
    if (arr != NULL) {
        rc = assoc_array_insert(arr, key1, num1);
        ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
        rc = assoc_array_insert(arr, key2, num2);
        ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
        rc = assoc_array_insert(arr, key3, num3);
        ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
        rc = assoc_array_max(arr, &nump);
        ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
        ck_assert_int_eq(num2, *nump);

        assoc_array_destroy(&arr);
    }
}
END_TEST

START_TEST(three_elems_third_max)
{
    const char *key1 = "key1";
    int num1 = 1;

    const char *key2 = "key2";
    int num2 = 2;

    const char *key3 = "key3";
    int num3 = 3;

    int *nump;

    assoc_array_t arr = assoc_array_create();
    assoc_array_error_t rc;
    if (arr != NULL) {
        rc = assoc_array_insert(arr, key1, num1);
        ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
        rc = assoc_array_insert(arr, key2, num2);
        ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
        rc = assoc_array_insert(arr, key3, num3);
        ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
        rc = assoc_array_max(arr, &nump);
        ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
        ck_assert_int_eq(num3, *nump);

        assoc_array_destroy(&arr);
    }
}
END_TEST

START_TEST(wrong_arr)
{
    const char *key1 = "a";
    int num = 1;
    int *nump;

    assoc_array_t arr = assoc_array_create();
    assoc_array_error_t rc;
    if (arr != NULL) {
        rc = assoc_array_insert(arr, key1, num);
        ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
        rc = assoc_array_max(NULL, &nump);
        ck_assert_int_eq(rc, ASSOC_ARRAY_INVALID_PARAM);
        assoc_array_destroy(&arr);
    }
}
END_TEST

START_TEST(wrong_key)
{
    const char *key1 = "a";
    int num = 1;

    assoc_array_t arr = assoc_array_create();
    assoc_array_error_t rc;
    if (arr != NULL) {
        rc = assoc_array_insert(arr, key1, num);
        ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
        rc = assoc_array_max(arr, NULL);
        ck_assert_int_eq(rc, ASSOC_ARRAY_INVALID_PARAM);
        assoc_array_destroy(&arr);
    }
}
END_TEST

Suite *assoc_array_max_suite()
{
    Suite *s;
    TCase *tc_core;

    s = suite_create("Max suite");
    tc_core = tcase_create("Max");

    tcase_add_test(tc_core, one_elem);
    tcase_add_test(tc_core, two_elems_first_max);
    tcase_add_test(tc_core, two_elems_second_max);
    tcase_add_test(tc_core, three_elems_first_max);
    tcase_add_test(tc_core, three_elems_second_max);
    tcase_add_test(tc_core, three_elems_third_max);

    tcase_add_test(tc_core, wrong_arr);
    tcase_add_test(tc_core, wrong_key);

    suite_add_tcase(s, tc_core);

    return s;
}
