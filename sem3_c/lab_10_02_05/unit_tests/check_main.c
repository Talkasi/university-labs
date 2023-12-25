#include "check_suites.h"
#include <check.h>

#define MAX_INT_N_BITS 64

int main()
{
    int number_failed;
    Suite *delete_dup_spaces_s;
    SRunner *delete_dup_spaces_sr;

    delete_dup_spaces_s = delete_dup_spaces_suite();
    delete_dup_spaces_sr = srunner_create(delete_dup_spaces_s);

    srunner_run_all(delete_dup_spaces_sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(delete_dup_spaces_sr);
    srunner_free(delete_dup_spaces_sr);

    Suite *concat_s;
    SRunner *concat_sr;

    concat_s = concat_suite();
    concat_sr = srunner_create(concat_s);

    srunner_run_all(concat_sr, CK_NORMAL);
    number_failed += srunner_ntests_failed(concat_sr);
    srunner_free(concat_sr);

    Suite *find_substr_s;
    SRunner *find_substr_sr;

    find_substr_s = find_substr_suite();
    find_substr_sr = srunner_create(find_substr_s);

    srunner_run_all(find_substr_sr, CK_NORMAL);
    number_failed += srunner_ntests_failed(find_substr_sr);
    srunner_free(find_substr_sr);

    return number_failed;
}
