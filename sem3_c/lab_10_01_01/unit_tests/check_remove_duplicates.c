#include "check.h"
#include "check_suites.h"
#include "check_tools.h"
#include "list.h"

START_TEST(empty_list)
{
    node_t *head_test = NULL;
    node_t *head_result = NULL;

    remove_duplicates(&head_test, ck_cmp_ints);
    ck_assert_mem_eq(&head_test, &head_result, sizeof(node_t *));
}
END_TEST

START_TEST(nothing_to_remove)
{
    node_t *head_test = NULL;
    node_t *head_result = NULL;

    int test[] = {1, 2, 3, 4, 5};
    size_t test_n = sizeof(test) / sizeof(test[0]);
    init_list_from_array(&head_test, test, test_n, sizeof(int));
    init_list_from_array(&head_result, test, test_n, sizeof(int));

    remove_duplicates(&head_test, ck_cmp_ints);
    ck_assert_int_eq(ck_lists_eq(head_test, head_result, ck_cmp_ints), 1);

    free_list(head_result);
    free_list(head_test);
}
END_TEST

START_TEST(first_to_remove)
{
    node_t *head_test = NULL;
    node_t *head_result = NULL;

    int test[] = {1, 1, 2, 3, 4, 5};
    int result[] = {1, 2, 3, 4, 5};
    size_t test_n = sizeof(test) / sizeof(test[0]);
    size_t result_n = sizeof(result) / sizeof(result[0]);
    init_list_from_array(&head_test, test, test_n, sizeof(int));
    init_list_from_array(&head_result, result, result_n, sizeof(int));

    remove_duplicates(&head_test, ck_cmp_ints);
    ck_assert_int_eq(ck_lists_eq(head_test, head_result, ck_cmp_ints), 1);

    free_list(head_result);
    free_list(head_test);
}
END_TEST

START_TEST(middle_to_remove)
{
    node_t *head_test = NULL;
    node_t *head_result = NULL;

    int test[] = {1, 2, 3, 3, 3, 4, 5};
    int result[] = {1, 2, 3, 4, 5};
    size_t test_n = sizeof(test) / sizeof(test[0]);
    size_t result_n = sizeof(result) / sizeof(result[0]);
    init_list_from_array(&head_test, test, test_n, sizeof(int));
    init_list_from_array(&head_result, result, result_n, sizeof(int));

    remove_duplicates(&head_test, ck_cmp_ints);
    ck_assert_int_eq(ck_lists_eq(head_test, head_result, ck_cmp_ints), 1);

    free_list(head_result);
    free_list(head_test);
}
END_TEST

START_TEST(last_to_remove)
{
    node_t *head_test = NULL;
    node_t *head_result = NULL;

    int test[] = {1, 2, 3, 4, 5, 5, 5};
    int result[] = {1, 2, 3, 4, 5};
    size_t test_n = sizeof(test) / sizeof(test[0]);
    size_t result_n = sizeof(result) / sizeof(result[0]);
    init_list_from_array(&head_test, test, test_n, sizeof(int));
    init_list_from_array(&head_result, result, result_n, sizeof(int));

    remove_duplicates(&head_test, ck_cmp_ints);
    ck_assert_int_eq(ck_lists_eq(head_test, head_result, ck_cmp_ints), 1);

    free_list(head_result);
    free_list(head_test);
}
END_TEST

START_TEST(different_duplicates_to_remove)
{
    node_t *head_test = NULL;
    node_t *head_result = NULL;

    int test[] = {1, 1, 1, 2, 3, 4, 4, 5, 5, 5};
    int result[] = {1, 2, 3, 4, 5};
    size_t test_n = sizeof(test) / sizeof(test[0]);
    size_t result_n = sizeof(result) / sizeof(result[0]);
    init_list_from_array(&head_test, test, test_n, sizeof(int));
    init_list_from_array(&head_result, result, result_n, sizeof(int));

    remove_duplicates(&head_test, ck_cmp_ints);
    ck_assert_int_eq(ck_lists_eq(head_test, head_result, ck_cmp_ints), 1);

    free_list(head_result);
    free_list(head_test);
}
END_TEST

Suite *remove_duplicates_suite()
{
    Suite *s;
    TCase *tc_core;

    s = suite_create("Remove duplicates suite");
    tc_core = tcase_create("Remove duplicates");

    tcase_add_test(tc_core, empty_list);
    tcase_add_test(tc_core, nothing_to_remove);
    tcase_add_test(tc_core, first_to_remove);
    tcase_add_test(tc_core, middle_to_remove);
    tcase_add_test(tc_core, last_to_remove);
    tcase_add_test(tc_core, different_duplicates_to_remove);

    suite_add_tcase(s, tc_core);

    return s;
}
