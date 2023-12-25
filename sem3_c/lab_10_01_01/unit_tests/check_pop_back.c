#include "check_suites.h"
#include "check_tools.h"
#include "list.h"
#include <check.h>

START_TEST(nothing_to_pop)
{
    node_t *head = NULL;

    void *expected = NULL;
    void *result = pop_back(&head);

    ck_assert_mem_eq(&result, &expected, sizeof(void *));
}
END_TEST

START_TEST(empty_list_remains)
{
    node_t *head_main = NULL;
    node_t *head_cp = NULL;
    char test[] = {'1'};
    size_t test_n = sizeof(test) / sizeof(test[0]);
    init_list_from_array(&head_main, test, test_n, sizeof(char));

    void *expected = &test[test_n - 1];
    void *result = pop_back(&head_main);

    ck_assert_mem_eq(&result, &expected, sizeof(void *));
    ck_assert_int_eq(ck_lists_eq(head_cp, head_main, ck_cmp_chars), 1);

    free_list(head_main);
    free_list(head_cp);
}
END_TEST

START_TEST(char_data_pop)
{
    node_t *head_main = NULL;
    node_t *head_cp = NULL;
    char test[] = {'1', '2'};
    size_t test_n = sizeof(test) / sizeof(test[0]);
    init_list_from_array(&head_main, test, test_n, sizeof(char));
    init_list_from_array(&head_cp, test, test_n - 1, sizeof(char));

    void *expected = &test[test_n - 1];
    void *result = pop_back(&head_main);

    ck_assert_mem_eq(&result, &expected, sizeof(void *));
    ck_assert_int_eq(ck_lists_eq(head_cp, head_main, ck_cmp_chars), 1);

    free_list(head_main);
    free_list(head_cp);
}
END_TEST

START_TEST(int_data_pop)
{
    node_t *head_main = NULL;
    node_t *head_cp = NULL;
    int test[] = {1, 2, 3};
    size_t test_n = sizeof(test) / sizeof(test[0]);
    init_list_from_array(&head_main, test, test_n, sizeof(int));
    init_list_from_array(&head_cp, test, test_n - 1, sizeof(int));

    void *expected = &test[test_n - 1];
    void *result = pop_back(&head_main);

    ck_assert_mem_eq(&result, &expected, sizeof(void *));
    ck_assert_int_eq(ck_lists_eq(head_cp, head_main, ck_cmp_ints), 1);

    free_list(head_main);
    free_list(head_cp);
}
END_TEST

START_TEST(double_data_pop)
{
    node_t *head_main = NULL;
    node_t *head_cp = NULL;
    double test[] = {1.2314, 0.1242, 334.34, 4};
    size_t test_n = sizeof(test) / sizeof(test[0]);
    init_list_from_array(&head_main, test, test_n, sizeof(double));
    init_list_from_array(&head_cp, test, test_n - 1, sizeof(double));

    void *expected = &test[test_n - 1];
    void *result = pop_back(&head_main);

    ck_assert_mem_eq(&result, &expected, sizeof(void *));
    ck_assert_int_eq(ck_lists_eq(head_cp, head_main, ck_cmp_doubles), 1);

    free_list(head_main);
    free_list(head_cp);
}
END_TEST

START_TEST(car_struct_data_pop)
{
    node_t *head_main = NULL;
    node_t *head_cp = NULL;
    car_t test[] = {
        {"UAS", 123456789, 2004, "Top secret"}, {"BMW", 987654321, 2020, "No name"}, {"No info", 0, 0, "No name"}};
    size_t test_n = sizeof(test) / sizeof(test[0]);
    init_list_from_array(&head_main, test, test_n, sizeof(car_t));
    init_list_from_array(&head_cp, test, test_n - 1, sizeof(car_t));

    void *expected = &test[test_n - 1];
    void *result = pop_back(&head_main);

    ck_assert_mem_eq(&result, &expected, sizeof(void *));
    ck_assert_int_eq(ck_lists_eq(head_cp, head_main, car_model_comparator), 1);

    free_list(head_main);
    free_list(head_cp);
}
END_TEST

Suite *pop_back_suite()
{
    Suite *s;
    TCase *tc_core;

    s = suite_create("Pop back suite");
    tc_core = tcase_create("Pop back");

    tcase_add_test(tc_core, nothing_to_pop);
    tcase_add_test(tc_core, empty_list_remains);
    tcase_add_test(tc_core, char_data_pop);
    tcase_add_test(tc_core, int_data_pop);
    tcase_add_test(tc_core, double_data_pop);
    tcase_add_test(tc_core, car_struct_data_pop);

    suite_add_tcase(s, tc_core);

    return s;
}
