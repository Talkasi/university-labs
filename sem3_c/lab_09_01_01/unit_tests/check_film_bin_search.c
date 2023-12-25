#include "check_film_bin_search.h"
#include "film.h"
#include <check.h>
#include <string.h>

void ck_film_arrs_equal(film_t *f1, film_t *f2, size_t len);

START_TEST(title_field_no_record)
{
    int field = TITLE;
    char *key = "Harry Potter";
    film_t test[] = {{"onion", "Onion", 1995}};

    size_t n_films = sizeof(test) / sizeof(test[0]);
    size_t result_i = n_films + 1;
    size_t i;

    film_t test_cp[n_films];
    memcpy(test_cp, test, sizeof(test));

    ck_assert_int_eq(films_bin_search(test, n_films, field, key, &i), 0);
    ck_assert_mem_eq(&result_i, &i, sizeof(size_t));

    ck_assert_mem_eq(test_cp, test, n_films);
}
END_TEST

START_TEST(name_field_no_record)
{
    int field = NAME;
    char *key = "Harry Potter";
    film_t test[] = {{"onion", "Onion", 1995}};

    size_t n_films = sizeof(test) / sizeof(test[0]);
    size_t result_i = n_films + 1;
    size_t i;

    film_t test_cp[n_films];
    memcpy(test_cp, test, sizeof(test));

    ck_assert_int_eq(films_bin_search(test, n_films, field, key, &i), 0);
    ck_assert_mem_eq(&result_i, &i, sizeof(size_t));

    ck_film_arrs_equal(test_cp, test, n_films);
}
END_TEST

START_TEST(year_field_no_record)
{
    int field = YEAR;
    char *key = "1";
    film_t test[] = {{"onion", "Onion", 1995}};

    size_t n_films = sizeof(test) / sizeof(test[0]);
    size_t result_i = n_films + 1;
    size_t i;

    film_t test_cp[n_films];
    memcpy(test_cp, test, sizeof(test));

    ck_assert_int_eq(films_bin_search(test, n_films, field, key, &i), 0);
    ck_assert_mem_eq(&result_i, &i, sizeof(size_t));

    ck_film_arrs_equal(test_cp, test, n_films);
}
END_TEST

START_TEST(title_field_first_record_needed)
{
    int field = TITLE;
    char *key = "onion";
    film_t test[] = {{"onion", "Onion", 1995}, {"zz", "zzzz", 234}, {"zzz", "234", 234}, {"zzzzzz", "23", 676}};

    size_t n_films = sizeof(test) / sizeof(test[0]);
    size_t result_i = 0;
    size_t i;

    film_t test_cp[n_films];
    memcpy(test_cp, test, sizeof(test));

    ck_assert_int_eq(films_bin_search(test, n_films, field, key, &i), 0);
    ck_assert_mem_eq(&result_i, &i, sizeof(size_t));

    ck_film_arrs_equal(test_cp, test, n_films);
}
END_TEST

START_TEST(name_field_first_record_needed)
{
    int field = NAME;
    char *key = "Onion";
    film_t test[] = {{"onion", "Onion", 1995}, {"zz", "zzzz", 234}, {"zzz", "z34", 234}, {"zzzzzz", "z23", 676}};
    size_t n_films = sizeof(test) / sizeof(test[0]);
    size_t result_i = 0;
    size_t i;

    film_t test_cp[n_films];
    memcpy(test_cp, test, sizeof(test));

    ck_assert_int_eq(films_bin_search(test, n_films, field, key, &i), 0);
    ck_assert_mem_eq(&result_i, &i, sizeof(size_t));

    ck_film_arrs_equal(test_cp, test, n_films);
}
END_TEST

START_TEST(year_field_first_record_needed)
{
    int field = YEAR;
    char *key = "1995";
    film_t test[] = {{"onion", "Onion", 1995}, {"zz", "zzzz", 2234}, {"zzz", "z34", 2234}, {"zzzzzz", "z23", 2676}};

    size_t n_films = sizeof(test) / sizeof(test[0]);
    size_t result_i = 0;
    size_t i;

    film_t test_cp[n_films];
    memcpy(test_cp, test, sizeof(test));

    ck_assert_int_eq(films_bin_search(test, n_films, field, key, &i), 0);
    ck_assert_mem_eq(&result_i, &i, sizeof(size_t));

    ck_film_arrs_equal(test_cp, test, n_films);
}
END_TEST

START_TEST(title_field_middle_record_needed)
{
    int field = TITLE;
    char *key = "zzz";
    film_t test[] = {{"onion", "Onion", 1995}, {"zz", "zzzz", 234}, {"zzz", "234", 234}, {"zzzzzz", "23", 676}};

    size_t n_films = sizeof(test) / sizeof(test[0]);
    size_t result_i = 2;
    size_t i;

    film_t test_cp[n_films];
    memcpy(test_cp, test, sizeof(test));

    ck_assert_int_eq(films_bin_search(test, n_films, field, key, &i), 0);
    ck_assert_mem_eq(&result_i, &i, sizeof(size_t));

    ck_film_arrs_equal(test_cp, test, n_films);
}
END_TEST

START_TEST(name_field_middle_record_needed)
{
    int field = NAME;
    char *key = "zzzz";
    film_t test[] = {{"onion", "Onion", 1995}, {"zz", "zzzz", 234}, {"zzz", "z34", 234}, {"zzzzzz", "z23", 676}};
    size_t n_films = sizeof(test) / sizeof(test[0]);
    size_t result_i = 1;
    size_t i;

    film_t test_cp[n_films];
    memcpy(test_cp, test, sizeof(test));

    ck_assert_int_eq(films_bin_search(test, n_films, field, key, &i), 0);
    ck_assert_mem_eq(&result_i, &i, sizeof(size_t));

    ck_film_arrs_equal(test_cp, test, n_films);
}
END_TEST

START_TEST(year_field_middle_record_needed)
{
    int field = YEAR;
    char *key = "2224";
    film_t test[] = {{"onion", "Onion", 1995}, {"zz", "zzzz", 2224}, {"zzz", "z34", 2234}, {"zzzzzz", "z23", 2676}};

    size_t n_films = sizeof(test) / sizeof(test[0]);
    size_t result_i = 1;
    size_t i;

    film_t test_cp[n_films];
    memcpy(test_cp, test, sizeof(test));

    ck_assert_int_eq(films_bin_search(test, n_films, field, key, &i), 0);
    ck_assert_mem_eq(&result_i, &i, sizeof(size_t));

    ck_film_arrs_equal(test_cp, test, n_films);
}
END_TEST

START_TEST(title_field_last_record_needed)
{
    int field = TITLE;
    char *key = "zzzzzz";
    film_t test[] = {{"onion", "Onion", 1995}, {"zz", "zzzz", 234}, {"zzz", "234", 234}, {"zzzzzz", "23", 676}};

    size_t n_films = sizeof(test) / sizeof(test[0]);
    size_t result_i = 3;
    size_t i;

    film_t test_cp[n_films];
    memcpy(test_cp, test, sizeof(test));

    ck_assert_int_eq(films_bin_search(test, n_films, field, key, &i), 0);
    ck_assert_mem_eq(&result_i, &i, sizeof(size_t));

    ck_film_arrs_equal(test_cp, test, n_films);
}
END_TEST

START_TEST(name_field_last_record_needed)
{
    int field = NAME;
    char *key = "z23";
    film_t test[] = {{"onion", "Onion", 1995}, {"zz", "z", 234}, {"zzz", "z14", 234}, {"zzzzzz", "z23", 676}};
    size_t n_films = sizeof(test) / sizeof(test[0]);
    size_t result_i = 3;
    size_t i;

    film_t test_cp[n_films];
    memcpy(test_cp, test, sizeof(test));

    ck_assert_int_eq(films_bin_search(test, n_films, field, key, &i), 0);
    ck_assert_mem_eq(&result_i, &i, sizeof(size_t));

    ck_film_arrs_equal(test_cp, test, n_films);
}
END_TEST

START_TEST(year_field_last_record_needed)
{
    int field = YEAR;
    char *key = "2676";
    film_t test[] = {{"onion", "Onion", 1111}, {"zz", "zzzz", 2222}, {"zzz", "z34", 2223},   {"zzzzzz", "z23", 2224},
                     {"zz", "zzzz", 2234},     {"zzz", "z34", 2235}, {"zzzzzz", "z23", 2676}};

    size_t n_films = sizeof(test) / sizeof(test[0]);
    size_t result_i = 6;
    size_t i;

    film_t test_cp[n_films];
    memcpy(test_cp, test, sizeof(test));

    ck_assert_int_eq(films_bin_search(test, n_films, field, key, &i), 0);
    ck_assert_mem_eq(&result_i, &i, sizeof(size_t));

    ck_film_arrs_equal(test_cp, test, n_films);
}
END_TEST

Suite *film_bin_search_suite()
{
    Suite *s;
    TCase *tc_core;

    s = suite_create("Film_bin_search");

    tc_core = tcase_create("Film_bin_search");

    tcase_add_test(tc_core, title_field_no_record);
    tcase_add_test(tc_core, name_field_no_record);
    tcase_add_test(tc_core, year_field_no_record);
    tcase_add_test(tc_core, title_field_first_record_needed);
    tcase_add_test(tc_core, name_field_first_record_needed);
    tcase_add_test(tc_core, year_field_first_record_needed);
    tcase_add_test(tc_core, title_field_middle_record_needed);
    tcase_add_test(tc_core, name_field_middle_record_needed);
    tcase_add_test(tc_core, year_field_middle_record_needed);
    tcase_add_test(tc_core, title_field_last_record_needed);
    tcase_add_test(tc_core, name_field_last_record_needed);
    tcase_add_test(tc_core, year_field_last_record_needed);
    suite_add_tcase(s, tc_core);

    return s;
}

void ck_film_arrs_equal(film_t *f1, film_t *f2, size_t len)
{
    for (size_t i = 0; i < len; ++i)
    {
        ck_assert_str_eq(f1[i].title, f2[i].title);
        ck_assert_str_eq(f1[i].name, f2[i].name);
        ck_assert_int_eq(f1[i].year, f2[i].year);
    }
}
