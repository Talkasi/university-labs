#include "check.h"
#include "check_suites.h"
#include "check_tools.h"
#include "list.h"

START_TEST(empty_list)
{
    node_t *head_test = NULL;
    node_t *head_result = NULL;

    head_test = sort(head_test, ck_cmp_ints);
    ck_assert_mem_eq(&head_test, &head_result, sizeof(node_t *));
}
END_TEST

START_TEST(int_data_one_elem)
{
    node_t *head_test = NULL;
    node_t *head_result = NULL;

    int test[] = {1};
    int result[] = {1};
    size_t test_n = sizeof(test) / sizeof(test[0]);
    size_t result_n = sizeof(result) / sizeof(result[0]);
    init_list_from_array(&head_test, test, test_n, sizeof(int));
    init_list_from_array(&head_result, result, result_n, sizeof(int));

    head_test = sort(head_test, ck_cmp_ints);
    ck_assert_int_eq(ck_lists_eq(head_test, head_result, ck_cmp_ints), 1);

    free_list(head_result);
    free_list(head_test);
}
END_TEST

START_TEST(int_data_two_sorted_elems)
{
    node_t *head_test = NULL;
    node_t *head_result = NULL;

    int test[] = {1, 2};
    int result[] = {1, 2};
    size_t test_n = sizeof(test) / sizeof(test[0]);
    size_t result_n = sizeof(result) / sizeof(result[0]);
    init_list_from_array(&head_test, test, test_n, sizeof(int));
    init_list_from_array(&head_result, result, result_n, sizeof(int));

    head_test = sort(head_test, ck_cmp_ints);
    ck_assert_int_eq(ck_lists_eq(head_test, head_result, ck_cmp_ints), 1);

    free_list(head_result);
    free_list(head_test);
}
END_TEST

START_TEST(int_data_two_unsorted_elems)
{
    node_t *head_test = NULL;
    node_t *head_result = NULL;

    int test[] = {2, 1};
    int result[] = {1, 2};
    size_t test_n = sizeof(test) / sizeof(test[0]);
    size_t result_n = sizeof(result) / sizeof(result[0]);
    init_list_from_array(&head_test, test, test_n, sizeof(int));
    init_list_from_array(&head_result, result, result_n, sizeof(int));

    head_test = sort(head_test, ck_cmp_ints);
    ck_assert_int_eq(ck_lists_eq(head_test, head_result, ck_cmp_ints), 1);

    free_list(head_result);
    free_list(head_test);
}
END_TEST

START_TEST(int_data_three_sorted_elems)
{
    node_t *head_test = NULL;
    node_t *head_result = NULL;

    int test[] = {1, 2, 3};
    int result[] = {1, 2, 3};
    size_t test_n = sizeof(test) / sizeof(test[0]);
    size_t result_n = sizeof(result) / sizeof(result[0]);
    init_list_from_array(&head_test, test, test_n, sizeof(int));
    init_list_from_array(&head_result, result, result_n, sizeof(int));

    head_test = sort(head_test, ck_cmp_ints);
    ck_assert_int_eq(ck_lists_eq(head_test, head_result, ck_cmp_ints), 1);

    free_list(head_result);
    free_list(head_test);
}
END_TEST

START_TEST(int_data_three_unsorted_elems)
{
    node_t *head_test = NULL;
    node_t *head_result = NULL;

    int test[] = {3, 2, 1};
    int result[] = {1, 2, 3};
    size_t test_n = sizeof(test) / sizeof(test[0]);
    size_t result_n = sizeof(result) / sizeof(result[0]);
    init_list_from_array(&head_test, test, test_n, sizeof(int));
    init_list_from_array(&head_result, result, result_n, sizeof(int));

    head_test = sort(head_test, ck_cmp_ints);
    ck_assert_int_eq(ck_lists_eq(head_test, head_result, ck_cmp_ints), 1);

    free_list(head_result);
    free_list(head_test);
}
END_TEST

START_TEST(int_data_four_sorted_elems)
{
    node_t *head_test = NULL;
    node_t *head_result = NULL;

    int test[] = {1, 2, 3, 4};
    int result[] = {1, 2, 3, 4};
    size_t test_n = sizeof(test) / sizeof(test[0]);
    size_t result_n = sizeof(result) / sizeof(result[0]);
    init_list_from_array(&head_test, test, test_n, sizeof(int));
    init_list_from_array(&head_result, result, result_n, sizeof(int));

    head_test = sort(head_test, ck_cmp_ints);
    ck_assert_int_eq(ck_lists_eq(head_test, head_result, ck_cmp_ints), 1);

    free_list(head_result);
    free_list(head_test);
}
END_TEST

START_TEST(int_data_four_unsorted_elems)
{
    node_t *head_test = NULL;
    node_t *head_result = NULL;

    int test[] = {4, 3, 2, 1};
    int result[] = {1, 2, 3, 4};
    size_t test_n = sizeof(test) / sizeof(test[0]);
    size_t result_n = sizeof(result) / sizeof(result[0]);
    init_list_from_array(&head_test, test, test_n, sizeof(int));
    init_list_from_array(&head_result, result, result_n, sizeof(int));

    head_test = sort(head_test, ck_cmp_ints);
    ck_assert_int_eq(ck_lists_eq(head_test, head_result, ck_cmp_ints), 1);

    free_list(head_result);
    free_list(head_test);
}
END_TEST

START_TEST(int_data_five_sorted_elems)
{
    node_t *head_test = NULL;
    node_t *head_result = NULL;

    int test[] = {1, 2, 3, 4, 5};
    int result[] = {1, 2, 3, 4, 5};
    size_t test_n = sizeof(test) / sizeof(test[0]);
    size_t result_n = sizeof(result) / sizeof(result[0]);
    init_list_from_array(&head_test, test, test_n, sizeof(int));
    init_list_from_array(&head_result, result, result_n, sizeof(int));

    head_test = sort(head_test, ck_cmp_ints);
    ck_assert_int_eq(ck_lists_eq(head_test, head_result, ck_cmp_ints), 1);

    free_list(head_result);
    free_list(head_test);
}
END_TEST

START_TEST(int_data_five_unsorted_elems)
{
    node_t *head_test = NULL;
    node_t *head_result = NULL;

    int test[] = {4, 3, 5, 2, 1};
    int result[] = {1, 2, 3, 4, 5};
    size_t test_n = sizeof(test) / sizeof(test[0]);
    size_t result_n = sizeof(result) / sizeof(result[0]);
    init_list_from_array(&head_test, test, test_n, sizeof(int));
    init_list_from_array(&head_result, result, result_n, sizeof(int));

    head_test = sort(head_test, ck_cmp_ints);
    ck_assert_int_eq(ck_lists_eq(head_test, head_result, ck_cmp_ints), 1);

    free_list(head_result);
    free_list(head_test);
}
END_TEST

Suite *sort_suite()
{
    Suite *s;
    TCase *tc_core;

    s = suite_create("Sort suite");
    tc_core = tcase_create("Sort");

    tcase_add_test(tc_core, empty_list);
    tcase_add_test(tc_core, int_data_one_elem);
    tcase_add_test(tc_core, int_data_two_sorted_elems);
    tcase_add_test(tc_core, int_data_two_unsorted_elems);
    tcase_add_test(tc_core, int_data_three_sorted_elems);
    tcase_add_test(tc_core, int_data_three_unsorted_elems);
    tcase_add_test(tc_core, int_data_four_sorted_elems);
    tcase_add_test(tc_core, int_data_four_unsorted_elems);
    tcase_add_test(tc_core, int_data_five_sorted_elems);
    tcase_add_test(tc_core, int_data_five_unsorted_elems);

    suite_add_tcase(s, tc_core);

    return s;
}
