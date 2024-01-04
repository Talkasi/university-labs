#include "big_nums.h"
#include <string.h>

int get_digit(bdouble_t *d, int digit_pos)
{
	int i = digit_pos / DIGITS_PER_LONG;
	int shift = DIGITS_PER_LONG - BITS_PER_DIGIT - (digit_pos % DIGITS_PER_LONG);
	return (d->mantissa[i] >> shift) & DIGIT_MASK;
}

// Puts digit on the position, doesn't shift bits.
void put_digit(bdouble_t *d, int digit_pos, int digit)
{
	int i = digit_pos % DIGITS_PER_LONG;
	int shift = DIGITS_PER_LONG - BITS_PER_DIGIT - (digit_pos % DIGITS_PER_LONG);

	d->mantissa[i] |= (digit & DIGIT_MASK) << shift;
}

int cmp_bdoubles(bdouble_t *d1, bdouble_t *d2)
{
	if (d1->d_in_mantissa != d2->d_in_mantissa)
		return d1->d_in_mantissa - d2->d_in_mantissa;

	for (int i = 0; i < d1->d_in_mantissa; ++i) {
		int d1_digit = get_digit(d1, i);
		int d2_digit = get_digit(d2, i);
		if (d1_digit != d2_digit)
			return d1_digit - d2_digit;
	}

	return 0;
}

int delete_prev_zeroes(bdouble_t *d)
{
	int n_prev_zeros = 0;
	for (int i = 0; i < d->d_in_mantissa; ++i)
		if (get_digit(d, i) == 0)
			++n_prev_zeros;
		else
			break;

	// NOTE (Talkasi): This part won't work.
	// TODO (Talkasi): Make up with sollution of bit - byte problem.
	memcpy(d->mantissa, d->mantissa + n_prev_zeros, (d->d_in_mantissa - n_prev_zeros) * BITS_PER_DIGIT);
	memset(d->mantissa + n_prev_zeros, 0, n_prev_zeros * BITS_PER_DIGIT);
	d->d_in_mantissa -= n_prev_zeros;

	return n_prev_zeros;
}

// Assumes that d1 >= d2, result is stored in d1.
int sub_bdoubles(bdouble_t *d1, bdouble_t *d2)
{
	int d2_shifter = d1->d_in_mantissa - d2->d_in_mantissa;
	int carry = 0;
	for (int i = d1->d_in_mantissa - 1; i >= 0; --i) {
		int new_digit = get_digit(d1, i) - get_digit(d2, i - d2_shifter) - carry;
		carry = (new_digit > 9) ? (new_digit - 9) : 0;
		put_digit(d1, i, new_digit);
	}

	return delete_prev_zeroes(d1);
}

int mul_bdouble(bdouble_t *res, bdouble_t *d, int num)
{
	memset(res, 0, sizeof(*res));

	int carry = 0;
	for (int i = d->d_in_mantissa; i > 0; --i) {
		int new_digit = get_digit(d, i - 1) * num + carry;
		carry = new_digit / 10;
		put_digit(res, i, new_digit);
	}

	put_digit(res, 0, carry);
	return delete_prev_zeroes(res);
}

int div_bdoubles(bdouble_t *res, bdouble_t *d1, bdouble_t *d2)
{
	memset(res, 0, sizeof(*res));
	int simple_divisor = get_digit(d2, 0);

	bdouble_t part_div = {};
	// NOTE (Talkasi): This part won't work.
	// TODO (Talkasi): Make up with sollution of bit - byte problem.
	memcpy(part_div.mantissa, d1->mantissa, d2->d_in_mantissa * BITS_PER_DIGIT);
	part_div.d_in_mantissa = d2->d_in_mantissa;

	int next_d1_digit_i = d2->d_in_mantissa;
	bdouble_t tmp_mul_res = {};
	int new_digit;
	do {
		while (part_div.d_in_mantissa < d2->d_in_mantissa) {
			if (next_d1_digit_i >= d1->d_in_mantissa && (part_div.d_in_mantissa == 0))
				return 0;

			new_digit = (next_d1_digit_i < d1->d_in_mantissa) ? get_digit(d1, next_d1_digit_i++) : 0;
			if (!(part_div.d_in_mantissa == 0) || (((part_div.d_in_mantissa == 0) && new_digit != 0)))
				put_digit(&part_div, part_div.d_in_mantissa++, new_digit);
		}

		int simple_dividend = get_digit(&part_div, 0);
		if (simple_dividend < simple_divisor) {
			simple_dividend = (simple_dividend * 10) + get_digit(&part_div, 1);
			new_digit = (next_d1_digit_i < d1->d_in_mantissa) ? get_digit(d1, next_d1_digit_i++) : 0;
			put_digit(&part_div, part_div.d_in_mantissa++, new_digit);
		}

		int simple_multiplier = simple_dividend / simple_divisor;
		mul_bdouble(&tmp_mul_res, &part_div, simple_multiplier);
		while (cmp_bdoubles(&tmp_mul_res, d2) > 0)
			mul_bdouble(&tmp_mul_res, &part_div, --simple_multiplier);

		put_digit(res, res->d_in_mantissa++, simple_multiplier);
		sub_bdoubles(&part_div, &tmp_mul_res);
	} while (next_d1_digit_i < d1->d_in_mantissa || !(part_div.d_in_mantissa == 0));

	return 0;
}
