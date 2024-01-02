#include "big_nums.h"
#include <assert.h>

int div_bdoubles(bdouble_t *res, bdouble_t d1, bdouble_t d2)
{
	memset(*res, 0, sizeof(*res));

	int simple_divisor = get_digit(d2, 0);

	bdouble_t part_div = {};
	memcpy(part_div.mantissa, d1.mantissa, d2.d_in_mantissa * BITS_PER_DIGIT);
	part_div.d_in_mantissa = d2.d_in_mantissa;

	int next_d1_digit_i = d2.d_in_mantissa;
	bdouble_t tmp_mul_res = {};
	int new_digit;
	do {
		while (part_div.d_in_mantissa < d2.d_in_mantissa) {
			if (next_d1_digit_i >= d1.d_in_mantissa && is_zero(part_div))
				return 0;

			new_digit = (next_d1_digit_i < d1.d_in_mantissa) ? get_digit(d1, next_d1_digit_i++) : 0;
			if (!is_zero(part_div) || ((is_zero(part_div) && new_digit != 0)))
				put_digit(&part_div, part_div.d_in_mantissa, new_digit);
		}

		simple_dividend = get_digit(part_div, 0);
		if (simple_dividend < simple_divisor) {
			simple_dividend = (simple_dividend * 10) + get_digit(part_div, 1);
			new_digit = (next_d1_digit_i < d1.d_in_mantissa) ? get_digit(d1, next_d1_digit_i++) : 0;
			put_digit(&part_div, part_div.d_in_mantissa, new_digit);
		}

		simple_multiplier = simple_dividend / simple_divisor;
		mul_bdouble(&tmp_mul_res, part_div, simple_multiplier);
		while (cmp_bdoubles(tmp_mul_res, d2) > 0)
			mul_bdouble(&tmp_mul_res, part_div, --simple_multiplier);

		put_digit(res, res.d_in_mantissa, simple_multiplier);
		sub_bdoubles(&part_div, tmp_mul_res);
	} while (next_d1_digit_i < d1.d_in_mantissa || !is_zero(part_div));

	return 0;
}

