#include "check_suites.h"
#include "check_tools.h"
#include "list.h"
#include <check.h>
#include <stdlib.h>

START_TEST(before_pointer_is_not_vailid)
{
    node_t *head_main = NULL;
    node_t *head_cp = NULL;
    int test[] = {1, 2, 3};
    size_t test_n = sizeof(test) / sizeof(test[0]);
    init_list_from_array(&head_main, test, test_n, sizeof(int));
    init_list_from_array(&head_cp, test, test_n, sizeof(int));

    node_t *elem;
    alloc_node(&elem);
    elem->data = &test[0];

    node_t *before = (node_t *)&test[0];

    insert(&head_main, elem, before);

    ck_assert_int_eq(ck_lists_eq(head_main, head_cp, ck_cmp_ints), 1);

    free_list(head_main);
    free_list(head_cp);
    free(elem);
}
END_TEST

START_TEST(empty_list)
{
    node_t *head_test = NULL;

    node_t *head_result = NULL;
    int test[] = {1};
    size_t test_n = sizeof(test) / sizeof(test[0]);
    init_list_from_array(&head_result, test, test_n, sizeof(int));

    node_t *elem;
    alloc_node(&elem);
    elem->data = &test[0];

    node_t *before = NULL;

    insert(&head_test, elem, before);

    ck_assert_int_eq(ck_lists_eq(head_test, head_result, ck_cmp_ints), 1);

    free_list(head_test);
    free_list(head_result);
}
END_TEST

START_TEST(start_insert)
{
    node_t *head_test = NULL;
    node_t *head_result = NULL;

    int test[] = {1, 2, 3};
    int result[] = {12, 1, 2, 3};
    int *to_insert = &result[0];

    size_t test_n = sizeof(test) / sizeof(test[0]);
    size_t result_n = sizeof(result) / sizeof(result[0]);
    init_list_from_array(&head_test, test, test_n, sizeof(int));
    init_list_from_array(&head_result, result, result_n, sizeof(int));

    node_t *elem;
    alloc_node(&elem);
    elem->data = to_insert;

    node_t *before = head_test;

    insert(&head_test, elem, before);

    ck_assert_int_eq(ck_lists_eq(head_test, head_result, ck_cmp_ints), 1);

    free_list(head_test);
    free_list(head_result);
}
END_TEST

START_TEST(middle_insert)
{
    node_t *head_test = NULL;
    node_t *head_result = NULL;

    int test[] = {1, 2, 3};
    int result[] = {1, 2, 4, 3};
    int i_to_insert = 2;

    size_t test_n = sizeof(test) / sizeof(test[0]);
    size_t result_n = sizeof(result) / sizeof(result[0]);
    init_list_from_array(&head_test, test, test_n, sizeof(int));
    init_list_from_array(&head_result, result, result_n, sizeof(int));

    node_t *elem;
    alloc_node(&elem);
    elem->data = &result[i_to_insert];

    node_t *before = ck_find_node_by_index(head_test, i_to_insert);

    insert(&head_test, elem, before);

    ck_assert_int_eq(ck_lists_eq(head_test, head_result, ck_cmp_ints), 1);

    free_list(head_test);
    free_list(head_result);
}
END_TEST

START_TEST(end_insert)
{
    node_t *head_test = NULL;
    node_t *head_result = NULL;

    int test[] = {1, 2, 3};
    int result[] = {1, 2, 3, 4};
    int i_to_insert = 3;

    size_t test_n = sizeof(test) / sizeof(test[0]);
    size_t result_n = sizeof(result) / sizeof(result[0]);
    init_list_from_array(&head_test, test, test_n, sizeof(int));
    init_list_from_array(&head_result, result, result_n, sizeof(int));

    node_t *elem;
    alloc_node(&elem);
    elem->data = &result[i_to_insert];

    node_t *before = ck_find_node_by_index(head_test, i_to_insert);

    insert(&head_test, elem, before);

    ck_assert_int_eq(ck_lists_eq(head_test, head_result, ck_cmp_ints), 1);

    free_list(head_test);
    free_list(head_result);
}
END_TEST

Suite *insert_suite()
{
    Suite *s;
    TCase *tc_core;

    s = suite_create("Insert suite");
    tc_core = tcase_create("Insert");

    tcase_add_test(tc_core, empty_list);
    tcase_add_test(tc_core, before_pointer_is_not_vailid);

    tcase_add_test(tc_core, start_insert);
    tcase_add_test(tc_core, middle_insert);
    tcase_add_test(tc_core, end_insert);

    suite_add_tcase(s, tc_core);

    return s;
}
