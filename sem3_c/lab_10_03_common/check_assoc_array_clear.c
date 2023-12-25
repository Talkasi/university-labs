#include "check_assoc_array_suites.h"
#include "associative_array.h"
#include <check.h>

START_TEST(one_elem)
{
    const char *key = "key";
    int num = 1;

    assoc_array_t arr = assoc_array_create();
    if (arr != NULL) {
        assoc_array_error_t rc = assoc_array_insert(arr, key, num);
        ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
        assoc_array_clear(arr);
        ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
        assoc_array_destroy(&arr);
    }
}
END_TEST

START_TEST(two_elems)
{
    const char *key1 = "key1";
    int num1 = 1;

    const char *key2 = "key2";
    int num2 = 1;

    assoc_array_t arr = assoc_array_create();
    assoc_array_error_t rc;
    if (arr != NULL) {
        rc = assoc_array_insert(arr, key1, num1);
        ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
        rc = assoc_array_insert(arr, key2, num2);
        ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
        assoc_array_clear(arr);
        ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
        assoc_array_destroy(&arr);
    }
}
END_TEST

START_TEST(three_elems)
{
    const char *key1 = "key1";
    int num1 = 1;

    const char *key2 = "key2";
    int num2 = 2;

    const char *key3 = "key3";
    int num3 = 3;

    assoc_array_t arr = assoc_array_create();
    assoc_array_error_t rc;
    if (arr != NULL) {
        rc = assoc_array_insert(arr, key1, num1);
        ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
        rc = assoc_array_insert(arr, key2, num2);
        ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
        rc = assoc_array_insert(arr, key3, num3);
        ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
        assoc_array_clear(arr);
        ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
        assoc_array_destroy(&arr);
    }
}
END_TEST


START_TEST(wrong_arr)
{
    const char *key = "a";
    int num = 1;

    assoc_array_t arr = assoc_array_create();
    assoc_array_error_t rc;
    if (arr != NULL) {
        rc = assoc_array_insert(arr, key, num);
        ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
        rc = assoc_array_clear(NULL);
        ck_assert_int_eq(rc, ASSOC_ARRAY_INVALID_PARAM);
        assoc_array_destroy(&arr);
    }
}
END_TEST

Suite *assoc_array_clear_suite()
{
    Suite *s;
    TCase *tc_core;

    s = suite_create("Clear suite");
    tc_core = tcase_create("Clear");

    tcase_add_test(tc_core, one_elem);
    tcase_add_test(tc_core, two_elems);
    tcase_add_test(tc_core, three_elems);

    tcase_add_test(tc_core, wrong_arr);

    suite_add_tcase(s, tc_core);

    return s;
}
