#include "check_suites.h"
#include "check_tools.h"
#include "list.h"
#include <check.h>

START_TEST(empty_list)
{
    size_t index = 0;
    size_t result_index = 0;
    node_t *head_string = NULL;
    node_t *head_substring = NULL;

    ck_assert_int_ne(find_substr(&index, head_string, head_substring), 0);
    ck_assert_mem_eq(&index, &result_index, sizeof(size_t));
}
END_TEST

START_TEST(only_spaces)
{
    char test_string[] = "         ";
    char test_substring[] = " ";
    size_t index;
    size_t result_index = 0;

    node_t *head_string = NULL;
    node_t *head_substring = NULL;

    init_list(&head_string, test_string);
    init_list(&head_substring, test_substring);

    ck_assert_int_eq(find_substr(&index, head_string, head_substring), 0);
    ck_assert_mem_eq(&index, &result_index, sizeof(size_t));

    free_list(&head_string);
    free_list(&head_substring);
}
END_TEST

START_TEST(in_the_middle)
{
    char test_string[] = "amama";
    char test_substring[] = "mam";
    size_t index;
    size_t result_index = 1;

    node_t *head_string = NULL;
    node_t *head_substring = NULL;

    init_list(&head_string, test_string);
    init_list(&head_substring, test_substring);

    ck_assert_int_eq(find_substr(&index, head_string, head_substring), 0);
    ck_assert_mem_eq(&index, &result_index, sizeof(size_t));

    free_list(&head_string);
    free_list(&head_substring);
}
END_TEST

START_TEST(several_variants)
{
    char test_string[] = "amamas";
    char test_substring[] = "ma";
    size_t index;
    size_t result_index = 1;

    node_t *head_string = NULL;
    node_t *head_substring = NULL;

    init_list(&head_string, test_string);
    init_list(&head_substring, test_substring);

    ck_assert_int_eq(find_substr(&index, head_string, head_substring), 0);
    ck_assert_mem_eq(&index, &result_index, sizeof(size_t));

    free_list(&head_string);
    free_list(&head_substring);
}
END_TEST

START_TEST(looped)
{
    char test_string[] = "mississippi";
    char test_substring[] = "issip";
    size_t index;
    size_t result_index = 4;

    node_t *head_string = NULL;
    node_t *head_substring = NULL;

    init_list(&head_string, test_string);
    init_list(&head_substring, test_substring);

    ck_assert_int_eq(find_substr(&index, head_string, head_substring), 0);
    ck_assert_mem_eq(&index, &result_index, sizeof(size_t));

    free_list(&head_string);
    free_list(&head_substring);
}
END_TEST

Suite *find_substr_suite()
{
    Suite *s;
    TCase *tc_core;

    s = suite_create("Find substring suite");
    tc_core = tcase_create("Find substring spaces");

    tcase_add_test(tc_core, empty_list);
    tcase_add_test(tc_core, only_spaces);
    tcase_add_test(tc_core, in_the_middle);
    tcase_add_test(tc_core, several_variants);
    tcase_add_test(tc_core, looped);

    suite_add_tcase(s, tc_core);

    return s;
}
