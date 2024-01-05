#include "big_nums.h"

int main()
{
	bdouble_t n;
	if (scanf_bdouble(&n))
		return SCANF_ERR;

	printf_bdouble(&n);
	return 0;
}
