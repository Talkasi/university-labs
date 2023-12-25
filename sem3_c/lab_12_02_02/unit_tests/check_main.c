#include "check_suites.h"
#include <check.h>

int main()
{
    int number_failed;
    Suite *init_arr_by_fib_s;
    SRunner *init_arr_by_fib_sr;

    init_arr_by_fib_s = init_arr_by_fib_suite();
    init_arr_by_fib_sr = srunner_create(init_arr_by_fib_s);

    srunner_run_all(init_arr_by_fib_sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(init_arr_by_fib_sr);
    srunner_free(init_arr_by_fib_sr);

    Suite *init_by_first_unique_s;
    SRunner *init_by_first_unique_sr;

    init_by_first_unique_s = init_by_first_unique_suite();
    init_by_first_unique_sr = srunner_create(init_by_first_unique_s);

    srunner_run_all(init_by_first_unique_sr, CK_NORMAL);
    number_failed += srunner_ntests_failed(init_by_first_unique_sr);
    srunner_free(init_by_first_unique_sr);

    return number_failed;
}
