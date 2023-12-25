#include "check_suites.h"
#include "check_tools.h"
#include "list.h"
#include <check.h>

START_TEST(empty_list)
{
    node_t *head_test = NULL;
    node_t *head_result = NULL;

    delete_dup_spaces(&head_test);
    ck_assert_mem_eq(&head_test, &head_result, sizeof(node_t *));
}
END_TEST

START_TEST(only_spaces)
{
    char test_string[] = "         ";
    char result_string[] = " ";

    node_t *head_test = NULL;
    node_t *head_result = NULL;

    init_list(&head_test, test_string);
    init_list(&head_result, result_string);

    delete_dup_spaces(&head_test);
    ck_lists_eq(head_test, head_result);

    free_list(&head_result);
    free_list(&head_test);
}
END_TEST

START_TEST(only_one_space)
{
    char test_string[] = " ";
    char result_string[] = " ";

    node_t *head_test = NULL;
    node_t *head_result = NULL;

    init_list(&head_test, test_string);
    init_list(&head_result, result_string);

    delete_dup_spaces(&head_test);
    ck_lists_eq(head_test, head_result);

    free_list(&head_result);
    free_list(&head_test);
}
END_TEST

START_TEST(no_spaces)
{
    char test_string[] = "sfdf";
    char result_string[] = "sfdf";

    node_t *head_test = NULL;
    node_t *head_result = NULL;

    init_list(&head_test, test_string);
    init_list(&head_result, result_string);

    delete_dup_spaces(&head_test);
    ck_lists_eq(head_test, head_result);

    free_list(&head_result);
    free_list(&head_test);
}
END_TEST

START_TEST(duplicated_spaces)
{
    char test_string[] = "s  s  s";
    char result_string[] = "s s s";

    node_t *head_test = NULL;
    node_t *head_result = NULL;

    init_list(&head_test, test_string);
    init_list(&head_result, result_string);

    delete_dup_spaces(&head_test);
    ck_lists_eq(head_test, head_result);

    free_list(&head_result);
    free_list(&head_test);
}
END_TEST

START_TEST(more_duplicated_spaces)
{
    char test_string[] = "s    s     s";
    char result_string[] = "s s s";

    node_t *head_test = NULL;
    node_t *head_result = NULL;

    init_list(&head_test, test_string);
    init_list(&head_result, result_string);

    delete_dup_spaces(&head_test);
    ck_lists_eq(head_test, head_result);

    free_list(&head_result);
    free_list(&head_test);
}
END_TEST

Suite *delete_dup_spaces_suite()
{
    Suite *s;
    TCase *tc_core;

    s = suite_create("Delete duplicated spaces suite");
    tc_core = tcase_create("Delete duplicated spaces");

    tcase_add_test(tc_core, empty_list);
    tcase_add_test(tc_core, only_spaces);
    tcase_add_test(tc_core, only_one_space);
    tcase_add_test(tc_core, no_spaces);
    tcase_add_test(tc_core, duplicated_spaces);
    tcase_add_test(tc_core, more_duplicated_spaces);

    suite_add_tcase(s, tc_core);

    return s;
}
