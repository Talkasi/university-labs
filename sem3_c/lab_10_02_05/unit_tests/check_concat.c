#include "check_suites.h"
#include "check_tools.h"
#include "list.h"
#include <check.h>

START_TEST(empty_lists)
{
    node_t *head_test1 = NULL;
    node_t *head_test2 = NULL;
    node_t *head_result = NULL;
    node_t *head_result_exp = NULL;

    concat(&head_result, head_test1, head_test2);
    ck_assert_mem_eq(&head_result, &head_result_exp, sizeof(node_t *));
}
END_TEST

START_TEST(first_is_null)
{
    node_t *head_test1 = NULL;
    node_t *head_test2 = NULL;
    node_t *head_result = NULL;
    node_t *head_result_exp = NULL;

    char *test2 = "a";
    char *result_exp = "a";

    init_list(&head_test2, test2);
    init_list(&head_result_exp, result_exp);

    concat(&head_result, head_test1, head_test2);
    ck_lists_eq(head_result, head_result_exp);

    free_list(&head_test1);
    free_list(&head_test2);
    free_list(&head_result);
    free_list(&head_result_exp);
}
END_TEST

START_TEST(second_is_null)
{
    node_t *head_test1 = NULL;
    node_t *head_test2 = NULL;
    node_t *head_result = NULL;
    node_t *head_result_exp = NULL;

    char *test1 = "a";
    char *result_exp = "a";

    init_list(&head_test1, test1);
    init_list(&head_result_exp, result_exp);

    concat(&head_result, head_test1, head_test2);
    ck_lists_eq(head_result, head_result_exp);

    free_list(&head_test1);
    free_list(&head_test2);
    free_list(&head_result);
    free_list(&head_result_exp);
}
END_TEST

START_TEST(two_chars_ans)
{
    node_t *head_test1 = NULL;
    node_t *head_test2 = NULL;
    node_t *head_result = NULL;
    node_t *head_result_exp = NULL;

    char *test1 = "a";
    char *test2 = "b";
    char *result_exp = "ab";

    init_list(&head_test1, test1);
    init_list(&head_test2, test2);
    init_list(&head_result_exp, result_exp);

    concat(&head_result, head_test1, head_test2);
    ck_lists_eq(head_result, head_result_exp);

    free_list(&head_test1);
    free_list(&head_test2);
    free_list(&head_result);
    free_list(&head_result_exp);
}
END_TEST

START_TEST(three_chars_ans)
{
    node_t *head_test1 = NULL;
    node_t *head_test2 = NULL;
    node_t *head_result = NULL;
    node_t *head_result_exp = NULL;

    char *test1 = "ab";
    char *test2 = "b";
    char *result_exp = "abb";

    init_list(&head_test1, test1);
    init_list(&head_test2, test2);
    init_list(&head_result_exp, result_exp);

    concat(&head_result, head_test1, head_test2);
    ck_lists_eq(head_result, head_result_exp);

    free_list(&head_test1);
    free_list(&head_test2);
    free_list(&head_result);
    free_list(&head_result_exp);
}
END_TEST

START_TEST(four_chars_ans)
{
    node_t *head_test1 = NULL;
    node_t *head_test2 = NULL;
    node_t *head_result = NULL;
    node_t *head_result_exp = NULL;

    char *test1 = "a";
    char *test2 = "bbb";
    char *result_exp = "abbb";

    init_list(&head_test1, test1);
    init_list(&head_test2, test2);
    init_list(&head_result_exp, result_exp);

    concat(&head_result, head_test1, head_test2);
    ck_lists_eq(head_result, head_result_exp);

    free_list(&head_test1);
    free_list(&head_test2);
    free_list(&head_result);
    free_list(&head_result_exp);
}
END_TEST

START_TEST(five_chars_ans)
{
    node_t *head_test1 = NULL;
    node_t *head_test2 = NULL;
    node_t *head_result = NULL;
    node_t *head_result_exp = NULL;

    char *test1 = "a";
    char *test2 = "bbsb";
    char *result_exp = "abbsb";

    init_list(&head_test1, test1);
    init_list(&head_test2, test2);
    init_list(&head_result_exp, result_exp);

    concat(&head_result, head_test1, head_test2);
    ck_lists_eq(head_result, head_result_exp);

    free_list(&head_test1);
    free_list(&head_test2);
    free_list(&head_result);
    free_list(&head_result_exp);
}
END_TEST

START_TEST(six_chars_ans)
{
    node_t *head_test1 = NULL;
    node_t *head_test2 = NULL;
    node_t *head_result = NULL;
    node_t *head_result_exp = NULL;

    char *test1 = "f";
    char *test2 = "abcde";
    char *result_exp = "fabcde";

    init_list(&head_test1, test1);
    init_list(&head_test2, test2);
    init_list(&head_result_exp, result_exp);

    concat(&head_result, head_test1, head_test2);
    ck_lists_eq(head_result, head_result_exp);

    free_list(&head_test1);
    free_list(&head_test2);
    free_list(&head_result);
    free_list(&head_result_exp);
}
END_TEST

Suite *concat_suite()
{
    Suite *s;
    TCase *tc_core;

    s = suite_create("Concatenate suite");
    tc_core = tcase_create("Concatenate spaces");

    tcase_add_test(tc_core, empty_lists);
    tcase_add_test(tc_core, two_chars_ans);
    tcase_add_test(tc_core, three_chars_ans);
    tcase_add_test(tc_core, four_chars_ans);
    tcase_add_test(tc_core, five_chars_ans);
    tcase_add_test(tc_core, first_is_null);
    tcase_add_test(tc_core, second_is_null);
    tcase_add_test(tc_core, six_chars_ans);

    suite_add_tcase(s, tc_core);

    return s;
}
