#include "big_nums.h"

int main()
{
	bdouble_t dividend = {};
	bdouble_t divisor = {};
	bdouble_t result = {};

	if (scanf_bdouble(&dividend) || scanf_bdouble(&divisor) || divisor.exponent != 0)
		return SCANF_ERR;

	div_bdoubles(&result, &dividend, &divisor);

	printf_bdouble(&dividend);
	printf_bdouble(&divisor);
	printf_bdouble(&result);

	return 0;
}
