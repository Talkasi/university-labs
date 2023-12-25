#ifndef CHECK_SUITES_H
#define CHECK_SUITES_H
#include <check.h>

Suite *find_suite();
Suite *pop_front_suite();
Suite *pop_back_suite();
Suite *insert_suite();
Suite *remove_duplicates_suite();
Suite *sort_suite();

#endif