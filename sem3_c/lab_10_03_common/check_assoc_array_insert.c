#include "check_assoc_array_suites.h"
#include "associative_array.h"
#include <check.h>

START_TEST(insert_two_key_exist_start)
{
    const char *key1 = "key1";
    int num1 = 1;

    const char *key2 = "key2";
    int num2 = 2;

    const char *key3 = "key3";
    int num3 = 3;

    const char *key4 = "key1";
    int num4 = 4;

    assoc_array_t arr = assoc_array_create();
    assoc_array_error_t rc;
    if (arr != NULL) {
        rc = assoc_array_insert(arr, key1, num1);
        ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
        rc = assoc_array_insert(arr, key2, num2);
        ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
        rc = assoc_array_insert(arr, key3, num3);
        ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
        rc = assoc_array_insert(arr, key4, num4);
        ck_assert_int_eq(rc, ASSOC_ARRAY_KEY_EXISTS);

        assoc_array_destroy(&arr);
    }
}
END_TEST

START_TEST(insert_two_key_exist_middle)
{
    const char *key1 = "key1";
    int num1 = 1;

    const char *key2 = "key2";
    int num2 = 2;

    const char *key3 = "key3";
    int num3 = 3;

    const char *key4 = "key2";
    int num4 = 4;

    assoc_array_t arr = assoc_array_create();
    assoc_array_error_t rc;
    if (arr != NULL) {
        rc = assoc_array_insert(arr, key1, num1);
        ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
        rc = assoc_array_insert(arr, key2, num2);
        ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
        rc = assoc_array_insert(arr, key3, num3);
        ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
        rc = assoc_array_insert(arr, key4, num4);
        ck_assert_int_eq(rc, ASSOC_ARRAY_KEY_EXISTS);

        assoc_array_destroy(&arr);
    }
}
END_TEST

START_TEST(insert_two_key_exist_end)
{
    const char *key1 = "key1";
    int num1 = 1;

    const char *key2 = "key2";
    int num2 = 2;

    const char *key3 = "key3";
    int num3 = 3;

    const char *key4 = "key3";
    int num4 = 4;

    assoc_array_t arr = assoc_array_create();
    assoc_array_error_t rc;
    if (arr != NULL) {
        rc = assoc_array_insert(arr, key1, num1);
        ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
        rc = assoc_array_insert(arr, key2, num2);
        ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
        rc = assoc_array_insert(arr, key3, num3);
        ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
        rc = assoc_array_insert(arr, key4, num4);
        ck_assert_int_eq(rc, ASSOC_ARRAY_KEY_EXISTS);

        assoc_array_destroy(&arr);
    }
}
END_TEST


START_TEST(insert_one)
{
    const char *key = "key";
    int num = 1;

    assoc_array_t arr = assoc_array_create();
    if (arr != NULL) {
        assoc_array_error_t rc = assoc_array_insert(arr, key, num);
        ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
        assoc_array_destroy(&arr);
    }
}
END_TEST

START_TEST(insert_two)
{
    const char *key1 = "key1";
    int num1 = 1;

    const char *key2 = "key2";
    int num2 = 2;

    assoc_array_t arr = assoc_array_create();
    assoc_array_error_t rc;
    if (arr != NULL) {
        rc = assoc_array_insert(arr, key1, num1);
        ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
        rc = assoc_array_insert(arr, key2, num2);
        ck_assert_int_eq(rc, ASSOC_ARRAY_OK);

        assoc_array_destroy(&arr);
    }
}
END_TEST

START_TEST(insert_three)
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

        assoc_array_destroy(&arr);
    }
}
END_TEST

START_TEST(wrong_arr)
{
    const char *key = "key";
    int num = 1;

    assoc_array_error_t rc = assoc_array_insert(NULL, key, num);
    ck_assert_int_eq(rc, ASSOC_ARRAY_INVALID_PARAM);
}
END_TEST

START_TEST(wrong_key)
{
    int num = 1;

    assoc_array_t arr = assoc_array_create();
    assoc_array_error_t rc;
    if (arr != NULL) {
        rc = assoc_array_insert(arr, NULL, num);
        ck_assert_int_eq(rc, ASSOC_ARRAY_INVALID_PARAM);
        assoc_array_destroy(&arr);
    }
}
END_TEST

START_TEST(empty_key)
{
    const char *key = "";
    int num = 1;

    assoc_array_t arr = assoc_array_create();
    assoc_array_error_t rc;
    if (arr != NULL) {
        rc = assoc_array_insert(arr, key, num);
        ck_assert_int_eq(rc, ASSOC_ARRAY_INVALID_PARAM);
        assoc_array_destroy(&arr);
    }
}
END_TEST

Suite *assoc_array_insert_suite()
{
    Suite *s;
    TCase *tc_core;

    s = suite_create("Insert suite");
    tc_core = tcase_create("Insert");

    tcase_add_test(tc_core, insert_two_key_exist_start);
    tcase_add_test(tc_core, insert_two_key_exist_end);
    tcase_add_test(tc_core, insert_two_key_exist_middle);
    tcase_add_test(tc_core, insert_one);
    tcase_add_test(tc_core, insert_two);
    tcase_add_test(tc_core, insert_three);

    tcase_add_test(tc_core, wrong_arr);
    tcase_add_test(tc_core, wrong_key);
    tcase_add_test(tc_core, empty_key);

    suite_add_tcase(s, tc_core);

    return s;
}
