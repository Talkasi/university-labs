#include "big_nums.h"
#include <stdio.h>

int main()
{
	bdouble_t d1 = {};
	bdouble_t d2 = {};

	if (scanf_bdouble(&d1) || scanf_bdouble(&d2))
		return SCANF_ERR;

	printf("%d\n", cmp_bdoubles(&d1, &d2));
	return 0;
}
