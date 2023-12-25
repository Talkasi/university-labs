#include "check_assoc_array_suites.h"
#include "associative_array.h"
#include <stdio.h>
#include <check.h>

//позитивные тесты для insert
START_TEST(test_insert_one)
{
    assoc_array_t arr = assoc_array_create();
    int *num = NULL;
    int rc = assoc_array_insert(arr, "alpha", 100);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    rc = assoc_array_find(arr, "alpha", &num);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    ck_assert_int_eq(*num, 100);
    assoc_array_destroy(&arr);
}

START_TEST(test_insert_several)
{
    assoc_array_t arr = assoc_array_create();
    int *num = NULL;
    int rc = assoc_array_insert(arr, "alpha", 100);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    rc = assoc_array_insert(arr, "beta", 99);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    rc = assoc_array_insert(arr, "gamma", 98);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);

    rc = assoc_array_find(arr, "alpha", &num);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    ck_assert_int_eq(*num, 100);

    rc = assoc_array_find(arr, "beta", &num);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    ck_assert_int_eq(*num, 99);

    rc = assoc_array_find(arr, "gamma", &num);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    ck_assert_int_eq(*num, 98);

    assoc_array_destroy(&arr);
}

//негативные тесты для insert
START_TEST(test_insert_empty_str)
{
    assoc_array_t arr = assoc_array_create();
    int rc = assoc_array_insert(arr, "\0", 100);
    ck_assert_int_eq(rc, ASSOC_ARRAY_INVALID_PARAM);
    assoc_array_destroy(&arr);
}

START_TEST(test_insert_null_str)
{
    assoc_array_t arr = assoc_array_create();
    char *s = NULL;
    int rc = assoc_array_insert(arr, s, 100);
    ck_assert_int_eq(rc, ASSOC_ARRAY_INVALID_PARAM);
    assoc_array_destroy(&arr);
}

START_TEST(test_insert_exists)
{
    assoc_array_t arr = assoc_array_create();
    int *num = NULL;
    int rc = assoc_array_insert(arr, "alpha", 100);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    rc = assoc_array_insert(arr, "alpha", 99);
    ck_assert_int_eq(rc, ASSOC_ARRAY_KEY_EXISTS);
    rc = assoc_array_insert(arr, "gamma", 98);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);

    rc = assoc_array_find(arr, "alpha", &num);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    ck_assert_int_eq(*num, 100);

    rc = assoc_array_find(arr, "gamma", &num);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    ck_assert_int_eq(*num, 98);

    assoc_array_destroy(&arr);
}

//позитивные тесты для find
START_TEST(test_find_one)
{
    assoc_array_t arr = assoc_array_create();
    int *num = NULL;
    int rc = assoc_array_insert(arr, "alpha", 100);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);

    rc = assoc_array_find(arr, "alpha", &num);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    ck_assert_int_eq(*num, 100);
    assoc_array_destroy(&arr);
}

START_TEST(test_find_several)
{
    assoc_array_t arr = assoc_array_create();
    int *num = NULL;
    int rc = assoc_array_insert(arr, "alpha", 100);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    rc = assoc_array_insert(arr, "beta", 99);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    rc = assoc_array_insert(arr, "gamma", 98);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);

    rc = assoc_array_find(arr, "alpha", &num);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    ck_assert_int_eq(*num, 100);

    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    rc = assoc_array_find(arr, "beta", &num);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    ck_assert_int_eq(*num, 99);

    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    rc = assoc_array_find(arr, "gamma", &num);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    ck_assert_int_eq(*num, 98);
    assoc_array_destroy(&arr);
}

//негативные тесты для find
START_TEST(test_find_no_matches)
{
    assoc_array_t arr = assoc_array_create();
    int *num = NULL;
    int rc = assoc_array_insert(arr, "alpha", 100);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    rc = assoc_array_insert(arr, "beta", 99);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    rc = assoc_array_insert(arr, "gamma", 98);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);

    rc = assoc_array_find(arr, "zulu", &num);
    ck_assert_int_eq(rc, ASSOC_ARRAY_NOT_FOUND);
    assoc_array_destroy(&arr);
}

//позитивные тесты для remove
START_TEST(test_remove_one)
{
    assoc_array_t arr = assoc_array_create();
    int rc = assoc_array_insert(arr, "alpha", 100);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);


    rc = assoc_array_remove(arr, "alpha");
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);

    int *num = NULL;
    rc = assoc_array_find(arr, "alpha", &num);
    ck_assert_int_eq(rc, ASSOC_ARRAY_NOT_FOUND);

    assoc_array_destroy(&arr);
}

START_TEST(test_remove_several)
{
    assoc_array_t arr = assoc_array_create();
    int rc = assoc_array_insert(arr, "alpha", 100);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    rc = assoc_array_insert(arr, "beta", 99);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    rc = assoc_array_insert(arr, "gamma", 98);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);

    int *num = NULL;
    rc = assoc_array_remove(arr, "alpha");
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    rc = assoc_array_find(arr, "alpha", &num);
    ck_assert_int_eq(rc, ASSOC_ARRAY_NOT_FOUND);

    rc = assoc_array_remove(arr, "beta");
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    rc = assoc_array_find(arr, "beta", &num);
    ck_assert_int_eq(rc, ASSOC_ARRAY_NOT_FOUND);
    rc = assoc_array_remove(arr, "gamma");
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    rc = assoc_array_find(arr, "gamma", &num);
    ck_assert_int_eq(rc, ASSOC_ARRAY_NOT_FOUND);

    assoc_array_destroy(&arr);
}

//негативные тесты для remove
START_TEST(test_remove_no_matches)
{
    assoc_array_t arr = assoc_array_create();
    int rc = assoc_array_insert(arr, "alpha", 100);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    rc = assoc_array_insert(arr, "beta", 99);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    rc = assoc_array_insert(arr, "gamma", 98);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);

    rc = assoc_array_remove(arr, "zulu");
    ck_assert_int_eq(rc, ASSOC_ARRAY_NOT_FOUND);
    assoc_array_destroy(&arr);
}

//позитивные тесты для min
START_TEST(test_min_several_sorted)
{
    assoc_array_t arr = assoc_array_create();
    int rc = assoc_array_insert(arr, "alpha", 100);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    rc = assoc_array_insert(arr, "beta", 99);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    rc = assoc_array_insert(arr, "gamma", 98);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);

    int *num = NULL;

    rc = assoc_array_min(arr, &num);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    ck_assert_int_eq(*num, 100);
    assoc_array_destroy(&arr);
}

START_TEST(test_min_several_anti_sorted)
{
    assoc_array_t arr = assoc_array_create();
    int rc = assoc_array_insert(arr, "zulu", 100);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    rc = assoc_array_insert(arr, "gamma", 99);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    rc = assoc_array_insert(arr, "alpha", 98);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);

    int *num = NULL;

    rc = assoc_array_min(arr, &num);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    ck_assert_int_eq(*num, 98);
    assoc_array_destroy(&arr);
}

//негативные тесты для min
START_TEST(test_min_null_arr)
{
    int *num = NULL;

    int rc = assoc_array_min(NULL, &num);
    ck_assert_int_eq(rc, ASSOC_ARRAY_INVALID_PARAM);
}

//позитивные тесты для max
START_TEST(test_max_several_sorted)
{
    assoc_array_t arr = assoc_array_create();
    int rc = assoc_array_insert(arr, "alpha", 100);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    rc = assoc_array_insert(arr, "beta", 99);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    rc = assoc_array_insert(arr, "gamma", 98);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);

    int *num = NULL;

    rc = assoc_array_max(arr, &num);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    ck_assert_int_eq(*num, 98);
    assoc_array_destroy(&arr);
}

START_TEST(test_max_several_anti_sorted)
{
    assoc_array_t arr = assoc_array_create();
    int rc = assoc_array_insert(arr, "zulu", 100);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    rc = assoc_array_insert(arr, "gamma", 99);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    rc = assoc_array_insert(arr, "alpha", 98);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);

    int *num = NULL;

    rc = assoc_array_max(arr, &num);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    ck_assert_int_eq(*num, 100);
    assoc_array_destroy(&arr);
}

//негативные тесты для max
START_TEST(test_max_null_arr)
{
    int *num = NULL;

    int rc = assoc_array_max(NULL, &num);
    ck_assert_int_eq(rc, ASSOC_ARRAY_INVALID_PARAM);
}

Suite* assoc_array_insert_suite(void)
{
    Suite *s;
    TCase *tc_neg;
    TCase *tc_pos;

    s = suite_create("insert");

    tc_neg = tcase_create("negatives");
    tcase_add_test(tc_neg, test_insert_empty_str);
    tcase_add_test(tc_neg, test_insert_null_str);
    tcase_add_test(tc_neg, test_insert_exists);
    suite_add_tcase(s, tc_neg);

    tc_pos = tcase_create("positives");
    tcase_add_test(tc_pos, test_insert_one);
    tcase_add_test(tc_pos, test_insert_several);
    suite_add_tcase(s, tc_pos);

    return s;
}

Suite* assoc_array_find_suite(void)
{
    Suite *s;
    TCase *tc_neg;
    TCase *tc_pos;

    s = suite_create("find");

    tc_neg = tcase_create("negatives");
    tcase_add_test(tc_neg, test_find_no_matches);
    suite_add_tcase(s, tc_neg);

    tc_pos = tcase_create("positives");
    tcase_add_test(tc_pos, test_find_one);
    tcase_add_test(tc_pos, test_find_several);
    suite_add_tcase(s, tc_pos);

    return s;
}

Suite* assoc_array_remove_suite(void)
{
    Suite *s;
    TCase *tc_neg;
    TCase *tc_pos;

    s = suite_create("remove");

    tc_neg = tcase_create("negatives");
    tcase_add_test(tc_neg, test_remove_no_matches);
    suite_add_tcase(s, tc_neg);

    tc_pos = tcase_create("positives");
    tcase_add_test(tc_pos, test_remove_one);
    tcase_add_test(tc_pos, test_remove_several);
    suite_add_tcase(s, tc_pos);

    return s;
}

Suite* assoc_array_min_suite(void)
{
    Suite *s;
    TCase *tc_neg;
    TCase *tc_pos;

    s = suite_create("min");

    tc_neg = tcase_create("negatives");
    tcase_add_test(tc_neg, test_min_null_arr);
    suite_add_tcase(s, tc_neg);

    tc_pos = tcase_create("positives");
    tcase_add_test(tc_pos, test_min_several_anti_sorted);
    tcase_add_test(tc_pos, test_min_several_sorted);
    suite_add_tcase(s, tc_pos);

    return s;
}

Suite* assoc_array_max_suite(void)
{
    Suite *s;
    TCase *tc_neg;
    TCase *tc_pos;

    s = suite_create("max");

    tc_neg = tcase_create("negatives");
    tcase_add_test(tc_neg, test_max_null_arr);
    suite_add_tcase(s, tc_neg);

    tc_pos = tcase_create("positives");
    tcase_add_test(tc_pos, test_max_several_anti_sorted);
    tcase_add_test(tc_pos, test_max_several_sorted);
    suite_add_tcase(s, tc_pos);

    return s;
}
