#include "check_suites.h"
#include <check.h>

#define MAX_INT_N_BITS 64

int main()
{
    int number_failed;
    Suite *find_s;
    SRunner *find_sr;

    find_s = find_suite();
    find_sr = srunner_create(find_s);

    srunner_run_all(find_sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(find_sr);
    srunner_free(find_sr);

    Suite *pop_front_s;
    SRunner *pop_front_sr;

    pop_front_s = pop_front_suite();
    pop_front_sr = srunner_create(pop_front_s);

    srunner_run_all(pop_front_sr, CK_NORMAL);
    number_failed += srunner_ntests_failed(pop_front_sr);
    srunner_free(pop_front_sr);

    Suite *pop_back_s;
    SRunner *pop_back_sr;

    pop_back_s = pop_back_suite();
    pop_back_sr = srunner_create(pop_back_s);

    srunner_run_all(pop_back_sr, CK_NORMAL);
    number_failed += srunner_ntests_failed(pop_back_sr);
    srunner_free(pop_back_sr);

    Suite *insert_s;
    SRunner *insert_sr;

    insert_s = insert_suite();
    insert_sr = srunner_create(insert_s);

    srunner_run_all(insert_sr, CK_NORMAL);
    number_failed += srunner_ntests_failed(insert_sr);
    srunner_free(insert_sr);

    Suite *remove_duplicates_s;
    SRunner *remove_duplicates_sr;

    remove_duplicates_s = remove_duplicates_suite();
    remove_duplicates_sr = srunner_create(remove_duplicates_s);

    srunner_run_all(remove_duplicates_sr, CK_NORMAL);
    number_failed += srunner_ntests_failed(remove_duplicates_sr);
    srunner_free(remove_duplicates_sr);

    Suite *sort_s;
    SRunner *sort_sr;

    sort_s = sort_suite();
    sort_sr = srunner_create(sort_s);

    srunner_run_all(sort_sr, CK_NORMAL);
    number_failed += srunner_ntests_failed(sort_sr);
    srunner_free(sort_sr);

    return number_failed;
}
