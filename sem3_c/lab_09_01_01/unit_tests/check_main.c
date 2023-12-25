#include "check_film_bin_search.h"
#include <check.h>

#define MAX_INT_N_BITS 64

int main()
{
    int number_failed;
    Suite *film_bin_search_s;
    SRunner *film_bin_search_sr;

    film_bin_search_s = film_bin_search_suite();
    film_bin_search_sr = srunner_create(film_bin_search_s);

    srunner_run_all(film_bin_search_sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(film_bin_search_sr);
    srunner_free(film_bin_search_sr);

    return number_failed;
}