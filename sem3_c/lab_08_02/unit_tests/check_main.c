#include "check_raise_matrix.h"
#include "check_square_by_add.h"
#include "check_square_by_del.h"
#include <check.h>

#define MAX_INT_N_BITS 64

int main()
{
    int number_failed;
    Suite *square_by_del_s;
    SRunner *square_by_del_sr;

    square_by_del_s = square_by_del_suite();
    square_by_del_sr = srunner_create(square_by_del_s);

    srunner_run_all(square_by_del_sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(square_by_del_sr);
    srunner_free(square_by_del_sr);

    Suite *square_by_add_s;
    SRunner *square_by_add_sr;

    square_by_add_s = square_by_add_suite();
    square_by_add_sr = srunner_create(square_by_add_s);

    srunner_run_all(square_by_add_sr, CK_NORMAL);
    number_failed += srunner_ntests_failed(square_by_add_sr) * MAX_INT_N_BITS;
    srunner_free(square_by_add_sr);

    Suite *raise_matrix_s;
    SRunner *raise_matrix_sr;

    raise_matrix_s = raise_matrix_suite();
    raise_matrix_sr = srunner_create(raise_matrix_s);

    srunner_run_all(raise_matrix_sr, CK_NORMAL);
    number_failed += srunner_ntests_failed(raise_matrix_sr) * MAX_INT_N_BITS * MAX_INT_N_BITS;
    srunner_free(raise_matrix_sr);

    return number_failed;
}