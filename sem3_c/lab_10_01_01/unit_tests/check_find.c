#include "check_suites.h"
#include "check_tools.h"
#include "list.h"
#include <check.h>
#include <math.h>

// TODO(Talkasi): Compare lists

START_TEST(int_data_nothing_to_find)
{
    int data = 0;
    int test[] = {1, 2, 3, 4, 5};
    size_t test_n = sizeof(test) / sizeof(test[0]);

    node_t *list = NULL;
    init_list_from_array(&list, test, test_n, sizeof(int));
    node_t *expected = NULL;

    node_t test_cp[test_n];
    memcpy(test_cp, test, sizeof(test));

    node_t *result = find(list, &data, ck_cmp_ints);

    ck_assert_mem_eq(&result, &expected, sizeof(node_t *));
    ck_assert_mem_eq(test_cp, test, test_n * sizeof(int));

    free_list(list);
}
END_TEST

START_TEST(int_data_first_to_find)
{
    node_t *list = NULL;
    size_t i_to_find = 0;

    int test[] = {1, 2, 3, 4, 5};
    int data = test[i_to_find];
    size_t test_n = sizeof(test) / sizeof(test[0]);

    init_list_from_array(&list, test, test_n, sizeof(int));
    node_t *expected = ck_find_node_by_index(list, i_to_find);

    int test_cp[test_n];
    memcpy(test_cp, test, sizeof(test));

    node_t *result = find(list, &data, ck_cmp_ints);

    ck_assert_mem_eq(&result, &expected, sizeof(node_t *));
    ck_assert_mem_eq(test_cp, test, test_n * sizeof(int));

    free_list(list);
}
END_TEST

START_TEST(int_data_middle_to_find)
{
    node_t *list = NULL;
    size_t i_to_find = 2;

    int test[] = {1, 2, 3, 4, 5};
    int data = test[i_to_find];
    size_t test_n = sizeof(test) / sizeof(test[0]);

    init_list_from_array(&list, test, test_n, sizeof(int));
    node_t *expected = ck_find_node_by_index(list, i_to_find);

    int test_cp[test_n];
    memcpy(test_cp, test, sizeof(test));

    node_t *result = find(list, &data, ck_cmp_ints);

    ck_assert_mem_eq(&result, &expected, sizeof(node_t *));
    ck_assert_mem_eq(test_cp, test, test_n * sizeof(int));

    free_list(list);
}
END_TEST

START_TEST(int_data_last_to_find)
{
    node_t *list = NULL;
    size_t i_to_find = 4;

    int test[] = {1, 2, 3, 4, 5};
    int data = test[i_to_find];
    size_t test_n = sizeof(test) / sizeof(test[0]);

    init_list_from_array(&list, test, test_n, sizeof(int));
    node_t *expected = ck_find_node_by_index(list, i_to_find);

    int test_cp[test_n];
    memcpy(test_cp, test, sizeof(test));

    node_t *result = find(list, &data, ck_cmp_ints);

    ck_assert_mem_eq(&result, &expected, sizeof(node_t *));
    ck_assert_mem_eq(test_cp, test, test_n * sizeof(int));

    free_list(list);
}
END_TEST

START_TEST(double_data_nothing_to_find)
{
    double data = 0;
    double test[] = {1.234, 0.23042, 0.2343, 434.234, 5.234};
    size_t test_n = sizeof(test) / sizeof(test[0]);

    node_t *list = NULL;
    init_list_from_array(&list, test, test_n, sizeof(double));
    node_t *expected = NULL;

    double test_cp[test_n];
    memcpy(test_cp, test, sizeof(test));

    node_t *result = find(list, &data, ck_cmp_doubles);

    ck_assert_mem_eq(&result, &expected, sizeof(node_t *));
    ck_assert_mem_eq(test_cp, test, test_n * sizeof(double));

    free_list(list);
}
END_TEST

START_TEST(double_data_first_to_find)
{
    node_t *list = NULL;
    size_t i_to_find = 0;

    double test[] = {1.234, 0.23042, 0.2343, 434.234, 5.234};
    double data = test[i_to_find];
    size_t test_n = sizeof(test) / sizeof(test[0]);

    init_list_from_array(&list, test, test_n, sizeof(double));
    node_t *expected = ck_find_node_by_index(list, i_to_find);

    double test_cp[test_n];
    memcpy(test_cp, test, sizeof(test));

    node_t *result = find(list, &data, ck_cmp_doubles);

    ck_assert_mem_eq(&result, &expected, sizeof(node_t *));
    ck_assert_mem_eq(test_cp, test, test_n * sizeof(double));

    free_list(list);
}
END_TEST

START_TEST(double_data_middle_to_find)
{
    node_t *list = NULL;
    size_t i_to_find = 2;

    double test[] = {1.234, 0.23042, 0.2343, 434.234, 5.234};
    double data = test[i_to_find];
    size_t test_n = sizeof(test) / sizeof(test[0]);

    init_list_from_array(&list, test, test_n, sizeof(double));
    node_t *expected = ck_find_node_by_index(list, i_to_find);

    double test_cp[test_n];
    memcpy(test_cp, test, sizeof(test));

    node_t *result = find(list, &data, ck_cmp_doubles);

    ck_assert_mem_eq(&result, &expected, sizeof(node_t *));
    ck_assert_mem_eq(test_cp, test, test_n * sizeof(double));

    free_list(list);
}
END_TEST

START_TEST(double_data_last_to_find)
{
    node_t *list = NULL;
    size_t i_to_find = 4;

    double test[] = {1.234, 0.23042, 0.2343, 434.234, 5.234};
    double data = test[i_to_find];
    size_t test_n = sizeof(test) / sizeof(test[0]);

    init_list_from_array(&list, test, test_n, sizeof(double));
    node_t *expected = ck_find_node_by_index(list, i_to_find);

    double test_cp[test_n];
    memcpy(test_cp, test, sizeof(test));

    node_t *result = find(list, &data, ck_cmp_doubles);

    ck_assert_mem_eq(&result, &expected, sizeof(node_t *));
    ck_assert_mem_eq(test_cp, test, test_n * sizeof(double));

    free_list(list);
}
END_TEST

START_TEST(car_struct_data_nothing_to_find)
{
    car_t data = {"a", 1, 2, "a"};
    car_t test[] = {
        {"UAS", 123456789, 2004, "Top secret"}, {"BMW", 987654321, 2020, "No name"}, {"No info", 0, 0, "No name"}};
    size_t test_n = sizeof(test) / sizeof(test[0]);

    node_t *list = NULL;
    init_list_from_array(&list, test, test_n, sizeof(car_t));
    node_t *expected = NULL;

    car_t test_cp[test_n];
    ck_cars_cpy(test_cp, test, test_n);

    node_t *result = find(list, &data, car_model_comparator);

    ck_assert_mem_eq(&result, &expected, sizeof(node_t *));
    ck_assert_int_eq(ck_cars_eq(test_cp, test, test_n), 1);

    free_list(list);
}
END_TEST

START_TEST(car_struct_data_first_to_find)
{
    node_t *list = NULL;
    size_t i_to_find = 0;

    car_t test[] = {
        {"UAS", 123456789, 2004, "Top secret"}, {"BMW", 987654321, 2020, "No name"}, {"No info", 0, 0, "No name"}};
    car_t data = test[i_to_find];
    size_t test_n = sizeof(test) / sizeof(test[0]);

    init_list_from_array(&list, test, test_n, sizeof(car_t));
    node_t *expected = ck_find_node_by_index(list, i_to_find);

    car_t test_cp[test_n];
    ck_cars_cpy(test_cp, test, test_n);

    node_t *result = find(list, &data, car_model_comparator);

    ck_assert_mem_eq(&result, &expected, sizeof(node_t *));
    ck_assert_int_eq(ck_cars_eq(test_cp, test, test_n), 1);

    free_list(list);
}
END_TEST

START_TEST(car_struct_data_middle_to_find)
{
    node_t *list = NULL;
    size_t i_to_find = 1;

    car_t test[] = {
        {"UAS", 123456789, 2004, "Top secret"}, {"BMW", 987654321, 2020, "No name"}, {"No info", 0, 0, "No name"}};
    car_t data = test[i_to_find];
    size_t test_n = sizeof(test) / sizeof(test[0]);

    init_list_from_array(&list, test, test_n, sizeof(car_t));
    node_t *expected = ck_find_node_by_index(list, i_to_find);

    car_t test_cp[test_n];
    ck_cars_cpy(test_cp, test, test_n);

    node_t *result = find(list, &data, car_model_comparator);

    ck_assert_mem_eq(&result, &expected, sizeof(node_t *));
    ck_assert_int_eq(ck_cars_eq(test_cp, test, test_n), 1);

    free_list(list);
}
END_TEST

START_TEST(car_struct_data_last_to_find)
{
    node_t *list = NULL;
    size_t i_to_find = 2;

    car_t test[] = {
        {"UAS", 123456789, 2004, "Top secret"}, {"BMW", 987654321, 2020, "No name"}, {"No info", 0, 0, "No name"}};
    car_t data = test[i_to_find];
    size_t test_n = sizeof(test) / sizeof(test[0]);

    init_list_from_array(&list, test, test_n, sizeof(car_t));
    node_t *expected = ck_find_node_by_index(list, i_to_find);

    car_t test_cp[test_n];
    ck_cars_cpy(test_cp, test, test_n);

    node_t *result = find(list, &data, car_model_comparator);

    ck_assert_mem_eq(&result, &expected, sizeof(node_t *));
    ck_assert_int_eq(ck_cars_eq(test_cp, test, test_n), 1);

    free_list(list);
}
END_TEST

Suite *find_suite()
{
    Suite *s;
    TCase *tc_core;

    s = suite_create("Find suite");
    tc_core = tcase_create("Find");

    tcase_add_test(tc_core, int_data_nothing_to_find);
    tcase_add_test(tc_core, int_data_first_to_find);
    tcase_add_test(tc_core, int_data_middle_to_find);
    tcase_add_test(tc_core, int_data_last_to_find);

    tcase_add_test(tc_core, double_data_nothing_to_find);
    tcase_add_test(tc_core, double_data_first_to_find);
    tcase_add_test(tc_core, double_data_middle_to_find);
    tcase_add_test(tc_core, double_data_last_to_find);

    tcase_add_test(tc_core, car_struct_data_nothing_to_find);
    tcase_add_test(tc_core, car_struct_data_first_to_find);
    tcase_add_test(tc_core, car_struct_data_middle_to_find);
    tcase_add_test(tc_core, car_struct_data_last_to_find);

    suite_add_tcase(s, tc_core);

    return s;
}
