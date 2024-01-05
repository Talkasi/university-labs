#include "big_nums.h"
#include <stdio.h>

int main()
{
	bdouble_t dividend = {};
	int divisor = 0;
	bdouble_t result = {};

	if (scanf_bdouble(&dividend) || scanf("%d", &divisor) != 1)
		return SCANF_ERR;

	mul_bdouble(&result, &dividend, divisor);
	printf_bdouble(&result);

	return 0;
}
