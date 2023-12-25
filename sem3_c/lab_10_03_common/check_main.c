#include "check_assoc_array_suites.h"
#include <check.h>

int main()
{
    int number_failed;

    Suite *assoc_array_insert_s;
    SRunner *assoc_array_insert_sr; 

    assoc_array_insert_s = assoc_array_insert_suite();
    assoc_array_insert_sr = srunner_create(assoc_array_insert_s);

    srunner_run_all(assoc_array_insert_sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(assoc_array_insert_sr);
    srunner_free(assoc_array_insert_sr);

    Suite *assoc_array_find_s;
    SRunner *assoc_array_find_sr;

    assoc_array_find_s = assoc_array_find_suite();
    assoc_array_find_sr = srunner_create(assoc_array_find_s);

    srunner_run_all(assoc_array_find_sr, CK_NORMAL);
    number_failed += srunner_ntests_failed(assoc_array_find_sr);
    srunner_free(assoc_array_find_sr);

    Suite *assoc_array_remove_s;
    SRunner *assoc_array_remove_sr;

    assoc_array_remove_s = assoc_array_remove_suite();
    assoc_array_remove_sr = srunner_create(assoc_array_remove_s);

    srunner_run_all(assoc_array_remove_sr, CK_NORMAL);
    number_failed += srunner_ntests_failed(assoc_array_remove_sr);
    srunner_free(assoc_array_remove_sr);

    Suite *assoc_array_clear_s;
    SRunner *assoc_array_clear_sr;

    assoc_array_clear_s = assoc_array_clear_suite();
    assoc_array_clear_sr = srunner_create(assoc_array_clear_s);

    srunner_run_all(assoc_array_clear_sr, CK_NORMAL);
    number_failed += srunner_ntests_failed(assoc_array_clear_sr);
    srunner_free(assoc_array_clear_sr);

    Suite *assoc_array_min_s;
    SRunner *assoc_array_min_sr;

    assoc_array_min_s = assoc_array_min_suite();
    assoc_array_min_sr = srunner_create(assoc_array_min_s);

    srunner_run_all(assoc_array_min_sr, CK_NORMAL);
    number_failed += srunner_ntests_failed(assoc_array_min_sr);
    srunner_free(assoc_array_min_sr);

    Suite *assoc_array_max_s;
    SRunner *assoc_array_max_sr;

    assoc_array_max_s = assoc_array_max_suite();
    assoc_array_max_sr = srunner_create(assoc_array_max_s);

    srunner_run_all(assoc_array_max_sr, CK_NORMAL);
    number_failed += srunner_ntests_failed(assoc_array_max_sr);
    srunner_free(assoc_array_max_sr);

    return number_failed;
}
