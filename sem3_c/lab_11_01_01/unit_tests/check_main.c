#include "check_my_snprintf.h"
#include <check.h>

int main()
{
    int number_failed;
    Suite *my_snprintf_s;
    SRunner *my_snprintf_sr;

    my_snprintf_s = my_snprintf_suite();
    my_snprintf_sr = srunner_create(my_snprintf_s);

    srunner_run_all(my_snprintf_sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(my_snprintf_sr);
    srunner_free(my_snprintf_sr);

    return number_failed;
}