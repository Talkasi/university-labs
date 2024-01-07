#include "big_nums.h"

int main()
{
    bdouble_t d1 = {};
    bdouble_t d2 = {};

    if (scanf_bdouble(&d1) || scanf_bdouble(&d2))
        return SCANF_ERR;

    sub_bdoubles(&d1, &d2);
    printf_bdouble_mantissa(&d1);
    return 0;
}
