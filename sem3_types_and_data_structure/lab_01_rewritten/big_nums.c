#include "big_nums.h"

int get_digit(bdouble_t *d, int digit_pos)
{
	int i = digit_pos / DIGITS_PER_LONG;
	int shift = DIGITS_PER_LONG - BITS_PER_DIGIT - (digit_pos % DIGITS_PER_LONG);
	return (d->mantissa[i] >> shift) & DIGIT_MASK;
}

void put_digit_to_end(bdouble_t *d, int digit)
{
	int i = digit_pos % DIGITS_PER_LONG;
	int shift = DIGITS_PER_LONG - BITS_PER_DIGIT - (digit_pos % DIGITS_PER_LONG);

	d->mantissa[i] |= (digit & DIGIT_MASK) << shift;
	++d->d_in_mantissa;
}

int cmp_bdoubles(bdouble_t *d1, bdouble_t *d2)
{
	if (d1->d_in_mantissa != d2->d_in_mantissa)
		return d1->d_in_mantissa - d2->d_in_mantissa;

	for (int i = 0; i < d1->d_in_mantissa; ++i) {
		d1_digit = get_digit(d1, i);
		d2_digit = get_digit(d2, i);
		if (d1_digit != d2_digit)
			return d1_digit - d2_digit;
	}

	return 0;
}

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
			if (next_d1_digit_i >= d1.d_in_mantissa && (part_div.d_in_maintissa == 0))
				return 0;

			new_digit = (next_d1_digit_i < d1.d_in_mantissa) ? get_digit(d1, next_d1_digit_i++) : 0;
			if (!(part_div.d_in_maintissa == 0) || (((part_div.d_in_maintissa == 0) && new_digit != 0)))
				put_digit_to_end(&part_div, new_digit);
		}

		simple_dividend = get_digit(part_div, 0);
		if (simple_dividend < simple_divisor) {
			simple_dividend = (simple_dividend * 10) + get_digit(part_div, 1);
			new_digit = (next_d1_digit_i < d1.d_in_mantissa) ? get_digit(d1, next_d1_digit_i++) : 0;
			put_digit_to_end(&part_div, new_digit);
		}

		simple_multiplier = simple_dividend / simple_divisor;
		mul_bdouble(&tmp_mul_res, part_div, simple_multiplier);
		while (cmp_bdoubles(tmp_mul_res, d2) > 0)
			mul_bdouble(&tmp_mul_res, part_div, --simple_multiplier);

		put_digit_to_end(res, simple_multiplier);
		sub_bdoubles(&part_div, tmp_mul_res);
	} while (next_d1_digit_i < d1.d_in_mantissa || !(part_div.d_in_maintissa == 0));

	return 0;
}
