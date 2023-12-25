#include "check_my_snprintf.h"
#include "my_snprintf.h"
#include <check.h>
#include <limits.h>
#include <stdio.h>

#define TEST_BUFFER_LEN 100

START_TEST(empty_format_string)
{
    char test_buffer[TEST_BUFFER_LEN];
    char result_buffer[TEST_BUFFER_LEN];
    char format[] = "";

    int test_rc = my_snprintf(test_buffer, TEST_BUFFER_LEN, format);
    int result_rc = snprintf(result_buffer, TEST_BUFFER_LEN, format);
    ck_assert_int_eq(test_rc, result_rc);
    ck_assert_mem_eq(test_buffer, result_buffer, result_rc < TEST_BUFFER_LEN ? result_rc : TEST_BUFFER_LEN);
}
END_TEST

START_TEST(one_char_no_format_flags)
{
    char test_buffer[TEST_BUFFER_LEN];
    char result_buffer[TEST_BUFFER_LEN];
    char format[] = "%c";

    char arg1 = 'a';

    int test_rc = my_snprintf(test_buffer, TEST_BUFFER_LEN, format, arg1);
    int result_rc = snprintf(result_buffer, TEST_BUFFER_LEN, format, arg1);
    ck_assert_int_eq(test_rc, result_rc);
    ck_assert_mem_eq(test_buffer, result_buffer, result_rc < TEST_BUFFER_LEN ? result_rc : TEST_BUFFER_LEN);
}
END_TEST

START_TEST(two_chars_no_format_flags_no_sep)
{
    char test_buffer[TEST_BUFFER_LEN];
    char result_buffer[TEST_BUFFER_LEN];
    char format[] = "%c%c";

    char arg1 = 'a';
    char arg2 = 'b';

    int test_rc = my_snprintf(test_buffer, TEST_BUFFER_LEN, format, arg1, arg2);
    int result_rc = snprintf(result_buffer, TEST_BUFFER_LEN, format, arg1, arg2);
    ck_assert_int_eq(test_rc, result_rc);
    ck_assert_mem_eq(test_buffer, result_buffer, result_rc < TEST_BUFFER_LEN ? result_rc : TEST_BUFFER_LEN);
}
END_TEST

START_TEST(two_chars_no_format_flags_with_sep_before)
{
    char test_buffer[TEST_BUFFER_LEN];
    char result_buffer[TEST_BUFFER_LEN];
    char format[] = "asd%c%c";

    char arg1 = 'a';
    char arg2 = 'b';

    int test_rc = my_snprintf(test_buffer, TEST_BUFFER_LEN, format, arg1, arg2);
    int result_rc = snprintf(result_buffer, TEST_BUFFER_LEN, format, arg1, arg2);
    ck_assert_int_eq(test_rc, result_rc);
    ck_assert_mem_eq(test_buffer, result_buffer, result_rc < TEST_BUFFER_LEN ? result_rc : TEST_BUFFER_LEN);
}
END_TEST

START_TEST(two_chars_no_format_flags_with_sep)
{
    char test_buffer[TEST_BUFFER_LEN];
    char result_buffer[TEST_BUFFER_LEN];
    char format[] = "asd %cs%c\n";

    char arg1 = 'a';
    char arg2 = 'b';

    int test_rc = my_snprintf(test_buffer, TEST_BUFFER_LEN, format, arg1, arg2);
    int result_rc = snprintf(result_buffer, TEST_BUFFER_LEN, format, arg1, arg2);
    ck_assert_int_eq(test_rc, result_rc);
    ck_assert_mem_eq(test_buffer, result_buffer, result_rc < TEST_BUFFER_LEN ? result_rc : TEST_BUFFER_LEN);
}
END_TEST

START_TEST(two_chars_no_format_flags_with_sep_after)
{
    char test_buffer[TEST_BUFFER_LEN];
    char result_buffer[TEST_BUFFER_LEN];
    char format[] = "%c%csadsd";

    char arg1 = 'a';
    char arg2 = 'b';

    int test_rc = my_snprintf(test_buffer, TEST_BUFFER_LEN, format, arg1, arg2);
    int result_rc = snprintf(result_buffer, TEST_BUFFER_LEN, format, arg1, arg2);
    ck_assert_int_eq(test_rc, result_rc);
    ck_assert_mem_eq(test_buffer, result_buffer, result_rc < TEST_BUFFER_LEN ? result_rc : TEST_BUFFER_LEN);
}
END_TEST

START_TEST(one_char_left_padding_no_sep)
{
    char test_buffer[TEST_BUFFER_LEN];
    char result_buffer[TEST_BUFFER_LEN];
    char format[] = "%03c";

    char arg1 = 'a';

    int test_rc = my_snprintf(test_buffer, TEST_BUFFER_LEN, format, arg1);
    int result_rc = snprintf(result_buffer, TEST_BUFFER_LEN, format, arg1);
    ck_assert_int_eq(test_rc, result_rc);
    ck_assert_mem_eq(test_buffer, result_buffer, result_rc < TEST_BUFFER_LEN ? result_rc : TEST_BUFFER_LEN);
}
END_TEST

START_TEST(one_char_width)
{
    char test_buffer[TEST_BUFFER_LEN];
    char result_buffer[TEST_BUFFER_LEN];
    char format[] = "%0800c";

    char arg1 = 'a';

    int test_rc = my_snprintf(test_buffer, TEST_BUFFER_LEN, format, arg1);
    int result_rc = snprintf(result_buffer, TEST_BUFFER_LEN, format, arg1);
    ck_assert_int_eq(test_rc, result_rc);
    ck_assert_mem_eq(test_buffer, result_buffer, result_rc < TEST_BUFFER_LEN ? result_rc : TEST_BUFFER_LEN);
}
END_TEST

START_TEST(one_int_no_format_flags)
{
    char test_buffer[TEST_BUFFER_LEN];
    char result_buffer[TEST_BUFFER_LEN];
    char format[] = "%d";

    int arg1 = 1234;

    int test_rc = my_snprintf(test_buffer, TEST_BUFFER_LEN, format, arg1);
    int result_rc = snprintf(result_buffer, TEST_BUFFER_LEN, format, arg1);
    ck_assert_int_eq(test_rc, result_rc);
    ck_assert_mem_eq(test_buffer, result_buffer, result_rc < TEST_BUFFER_LEN ? result_rc : TEST_BUFFER_LEN);
}
END_TEST

START_TEST(two_ints_no_format_flags_no_sep)
{
    char test_buffer[TEST_BUFFER_LEN];
    char result_buffer[TEST_BUFFER_LEN];
    char format[] = "%d%d";

    int arg1 = 23;
    int arg2 = 14;

    int test_rc = my_snprintf(test_buffer, TEST_BUFFER_LEN, format, arg1, arg2);
    int result_rc = snprintf(result_buffer, TEST_BUFFER_LEN, format, arg1, arg2);
    ck_assert_int_eq(test_rc, result_rc);
    ck_assert_mem_eq(test_buffer, result_buffer, result_rc < TEST_BUFFER_LEN ? result_rc : TEST_BUFFER_LEN);
}
END_TEST

START_TEST(two_ints_no_format_flags_with_sep_before)
{
    char test_buffer[TEST_BUFFER_LEN];
    char result_buffer[TEST_BUFFER_LEN];
    char format[] = "asd%d%d";

    int arg1 = 12;
    int arg2 = 23;

    int test_rc = my_snprintf(test_buffer, TEST_BUFFER_LEN, format, arg1, arg2);
    int result_rc = snprintf(result_buffer, TEST_BUFFER_LEN, format, arg1, arg2);
    ck_assert_int_eq(test_rc, result_rc);
    ck_assert_mem_eq(test_buffer, result_buffer, result_rc < TEST_BUFFER_LEN ? result_rc : TEST_BUFFER_LEN);
}
END_TEST

START_TEST(two_ints_no_format_flags_with_sep)
{
    char test_buffer[TEST_BUFFER_LEN];
    char result_buffer[TEST_BUFFER_LEN];
    char format[] = "asd %ds%d\n";

    int arg1 = 12;
    int arg2 = 23;

    int test_rc = my_snprintf(test_buffer, TEST_BUFFER_LEN, format, arg1, arg2);
    int result_rc = snprintf(result_buffer, TEST_BUFFER_LEN, format, arg1, arg2);
    ck_assert_int_eq(test_rc, result_rc);
    ck_assert_mem_eq(test_buffer, result_buffer, result_rc < TEST_BUFFER_LEN ? result_rc : TEST_BUFFER_LEN);
}
END_TEST

START_TEST(two_ints_no_format_flags_with_sep_after)
{
    char test_buffer[TEST_BUFFER_LEN];
    char result_buffer[TEST_BUFFER_LEN];
    char format[] = "%d%dsadsd";

    int arg1 = 12;
    int arg2 = 23;

    int test_rc = my_snprintf(test_buffer, TEST_BUFFER_LEN, format, arg1, arg2);
    int result_rc = snprintf(result_buffer, TEST_BUFFER_LEN, format, arg1, arg2);
    ck_assert_int_eq(test_rc, result_rc);
    ck_assert_mem_eq(test_buffer, result_buffer, result_rc < TEST_BUFFER_LEN ? result_rc : TEST_BUFFER_LEN);
}
END_TEST

START_TEST(one_int_left_padding_no_sep)
{
    char test_buffer[TEST_BUFFER_LEN];
    char result_buffer[TEST_BUFFER_LEN];
    char format[] = "%03d";

    int arg1 = 12;

    int test_rc = my_snprintf(test_buffer, TEST_BUFFER_LEN, format, arg1);
    int result_rc = snprintf(result_buffer, TEST_BUFFER_LEN, format, arg1);
    ck_assert_int_eq(test_rc, result_rc);
    ck_assert_mem_eq(test_buffer, result_buffer, result_rc < TEST_BUFFER_LEN ? result_rc : TEST_BUFFER_LEN);
}
END_TEST

START_TEST(one_int_zero)
{
    char test_buffer[TEST_BUFFER_LEN];
    char result_buffer[TEST_BUFFER_LEN];
    char format[] = "%d";

    int arg1 = 0;

    int test_rc = my_snprintf(test_buffer, TEST_BUFFER_LEN, format, arg1);
    int result_rc = snprintf(result_buffer, TEST_BUFFER_LEN, format, arg1);
    ck_assert_int_eq(test_rc, result_rc);
    ck_assert_mem_eq(test_buffer, result_buffer, result_rc < TEST_BUFFER_LEN ? result_rc : TEST_BUFFER_LEN);
}
END_TEST

START_TEST(one_int_max)
{
    char test_buffer[TEST_BUFFER_LEN];
    char result_buffer[TEST_BUFFER_LEN];
    char format[] = "ва%d";

    int arg1 = INT_MAX;

    int test_rc = my_snprintf(test_buffer, TEST_BUFFER_LEN, format, arg1);
    int result_rc = snprintf(result_buffer, TEST_BUFFER_LEN, format, arg1);
    ck_assert_int_eq(test_rc, result_rc);
    ck_assert_mem_eq(test_buffer, result_buffer, result_rc < TEST_BUFFER_LEN ? result_rc : TEST_BUFFER_LEN);
}
END_TEST

START_TEST(one_int_min)
{
    char test_buffer[TEST_BUFFER_LEN];
    char result_buffer[TEST_BUFFER_LEN];
    char format[] = "%500dав";

    int arg1 = INT_MIN;

    int test_rc = my_snprintf(test_buffer, TEST_BUFFER_LEN, format, arg1);
    int result_rc = snprintf(result_buffer, TEST_BUFFER_LEN, format, arg1);
    ck_assert_int_eq(test_rc, result_rc);
    ck_assert_mem_eq(test_buffer, result_buffer, result_rc < TEST_BUFFER_LEN ? result_rc : TEST_BUFFER_LEN);
}
END_TEST

START_TEST(one_int_max_prec_flag)
{
    char test_buffer[TEST_BUFFER_LEN];
    char result_buffer[TEST_BUFFER_LEN];
    char format[] = "%.5d";

    int arg1 = INT_MAX;

    int test_rc = my_snprintf(test_buffer, TEST_BUFFER_LEN, format, arg1);
    int result_rc = snprintf(result_buffer, TEST_BUFFER_LEN, format, arg1);
    ck_assert_int_eq(test_rc, result_rc);
    ck_assert_mem_eq(test_buffer, result_buffer, result_rc < TEST_BUFFER_LEN ? result_rc : TEST_BUFFER_LEN);
}
END_TEST

START_TEST(one_int_min_prec_flag)
{
    char test_buffer[TEST_BUFFER_LEN];
    char result_buffer[TEST_BUFFER_LEN];
    char format[] = "%.5d";

    int arg1 = INT_MIN;

    int test_rc = my_snprintf(test_buffer, TEST_BUFFER_LEN, format, arg1);
    int result_rc = snprintf(result_buffer, TEST_BUFFER_LEN, format, arg1);
    ck_assert_int_eq(test_rc, result_rc);
    ck_assert_mem_eq(test_buffer, result_buffer, result_rc < TEST_BUFFER_LEN ? result_rc : TEST_BUFFER_LEN);
}
END_TEST

START_TEST(one_int_min_prec_and_min_width_flag)
{
    char test_buffer[TEST_BUFFER_LEN];
    char result_buffer[TEST_BUFFER_LEN];
    char format[] = "%50.500d\n\t\n";

    int arg1 = INT_MIN;

    int test_rc = my_snprintf(test_buffer, TEST_BUFFER_LEN, format, arg1);
    int result_rc = snprintf(result_buffer, TEST_BUFFER_LEN, format, arg1);
    ck_assert_int_eq(test_rc, result_rc);
    ck_assert_mem_eq(test_buffer, result_buffer, result_rc < TEST_BUFFER_LEN ? result_rc : TEST_BUFFER_LEN);
}
END_TEST

START_TEST(int_signed)
{
    char test_buffer[TEST_BUFFER_LEN];
    char result_buffer[TEST_BUFFER_LEN];
    char format[] = "%+d";

    int arg1 = INT_MAX;

    int test_rc = my_snprintf(test_buffer, TEST_BUFFER_LEN, format, arg1);
    int result_rc = snprintf(result_buffer, TEST_BUFFER_LEN, format, arg1);
    ck_assert_int_eq(test_rc, result_rc);
    ck_assert_mem_eq(test_buffer, result_buffer, result_rc < TEST_BUFFER_LEN ? result_rc : TEST_BUFFER_LEN);
}
END_TEST

START_TEST(int_signed_space)
{
    char test_buffer[TEST_BUFFER_LEN];
    char result_buffer[TEST_BUFFER_LEN];
    char format[] = "% d";

    int arg1 = INT_MAX;

    int test_rc = my_snprintf(test_buffer, TEST_BUFFER_LEN, format, arg1);
    int result_rc = snprintf(result_buffer, TEST_BUFFER_LEN, format, arg1);
    ck_assert_int_eq(test_rc, result_rc);
    ck_assert_mem_eq(test_buffer, result_buffer, result_rc < TEST_BUFFER_LEN ? result_rc : TEST_BUFFER_LEN);
}
END_TEST

START_TEST(int_max_formatting)
{
    char test_buffer[TEST_BUFFER_LEN];
    char result_buffer[TEST_BUFFER_LEN];
    char format[] = "%-.50d";

    int arg1 = INT_MAX;

    int test_rc = my_snprintf(test_buffer, TEST_BUFFER_LEN, format, arg1);
    int result_rc = snprintf(result_buffer, TEST_BUFFER_LEN, format, arg1);
    ck_assert_int_eq(test_rc, result_rc);
    ck_assert_mem_eq(test_buffer, result_buffer, result_rc < TEST_BUFFER_LEN ? result_rc : TEST_BUFFER_LEN);
}
END_TEST

START_TEST(int_formatting)
{
    char test_buffer[TEST_BUFFER_LEN];
    char result_buffer[TEST_BUFFER_LEN];
    char format[] = "%-3.3d";

    int arg1 = -91;

    int test_rc = my_snprintf(test_buffer, TEST_BUFFER_LEN, format, arg1);
    int result_rc = snprintf(result_buffer, TEST_BUFFER_LEN, format, arg1);
    ck_assert_int_eq(test_rc, result_rc);
    ck_assert_mem_eq(test_buffer, result_buffer, result_rc < TEST_BUFFER_LEN ? result_rc : TEST_BUFFER_LEN);
}
END_TEST

START_TEST(int_zero_dot)
{
    char test_buffer[TEST_BUFFER_LEN];
    char result_buffer[TEST_BUFFER_LEN];
    char format[] = "%.0d";

    int arg1 = 0;

    int test_rc = my_snprintf(test_buffer, TEST_BUFFER_LEN, format, arg1);
    int result_rc = snprintf(result_buffer, TEST_BUFFER_LEN, format, arg1);
    ck_assert_int_eq(test_rc, result_rc);
    ck_assert_mem_eq(test_buffer, result_buffer, result_rc < TEST_BUFFER_LEN ? result_rc : TEST_BUFFER_LEN);
}
END_TEST

START_TEST(zero_length_buffer)
{
    char test_buffer[TEST_BUFFER_LEN];
    char result_buffer[TEST_BUFFER_LEN];
    char format[] = "%.0d";

    int arg1 = 1;

    int test_rc = my_snprintf(test_buffer, 0, format, arg1);
    int result_rc = snprintf(result_buffer, 0, format, arg1);
    ck_assert_int_eq(test_rc, result_rc);
}
END_TEST

Suite *my_snprintf_suite()
{
    Suite *s;
    TCase *tc_core;

    s = suite_create("My snprintf suite");
    tc_core = tcase_create("My snprintf");

    tcase_add_test(tc_core, empty_format_string);
    tcase_add_test(tc_core, one_char_no_format_flags);
    tcase_add_test(tc_core, two_chars_no_format_flags_no_sep);
    tcase_add_test(tc_core, two_chars_no_format_flags_with_sep_before);
    tcase_add_test(tc_core, two_chars_no_format_flags_with_sep);
    tcase_add_test(tc_core, two_chars_no_format_flags_with_sep_after);
    tcase_add_test(tc_core, one_char_left_padding_no_sep);
    tcase_add_test(tc_core, one_int_no_format_flags);
    tcase_add_test(tc_core, two_ints_no_format_flags_no_sep);
    tcase_add_test(tc_core, two_ints_no_format_flags_with_sep_before);
    tcase_add_test(tc_core, two_ints_no_format_flags_with_sep);
    tcase_add_test(tc_core, two_ints_no_format_flags_with_sep_after);
    tcase_add_test(tc_core, one_int_left_padding_no_sep);
    tcase_add_test(tc_core, one_int_zero);
    tcase_add_test(tc_core, one_int_max);
    tcase_add_test(tc_core, one_int_min);
    tcase_add_test(tc_core, one_int_max_prec_flag);
    tcase_add_test(tc_core, one_int_min_prec_flag);
    tcase_add_test(tc_core, one_int_min_prec_and_min_width_flag);
    tcase_add_test(tc_core, int_signed_space);
    tcase_add_test(tc_core, int_signed);
    tcase_add_test(tc_core, int_max_formatting);
    tcase_add_test(tc_core, int_formatting);
    tcase_add_test(tc_core, int_zero_dot);
    tcase_add_test(tc_core, one_char_width);
    tcase_add_test(tc_core, zero_length_buffer);

    suite_add_tcase(s, tc_core);

    return s;
}
