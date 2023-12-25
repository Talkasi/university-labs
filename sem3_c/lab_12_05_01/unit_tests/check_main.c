#include "check_key.h"
#include "check_mysort.h"
#include <check.h>

int main()
{
    int number_failed;
    Suite *key_s;
    SRunner *key_sr;

    key_s = key_suite();
    key_sr = srunner_create(key_s);

    srunner_run_all(key_sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(key_sr);
    srunner_free(key_sr);

    Suite *mysort_s;
    SRunner *mysort_sr;

    mysort_s = mysort_suite();
    mysort_sr = srunner_create(mysort_s);

    srunner_run_all(mysort_sr, CK_NORMAL);
    number_failed += srunner_ntests_failed(mysort_sr);
    srunner_free(mysort_sr);

    return number_failed;
}
