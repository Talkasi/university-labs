#include "big_nums.h"
#include <stdio.h>
#include <string.h>

int get_digit(bdouble_t *d, int digit_pos)
{
	int i = digit_pos / DIGITS_PER_LONG;
	int shift = BITS_IN_LONG - ((digit_pos + 1) % DIGITS_PER_LONG) * BITS_PER_DIGIT;
	return (d->mantissa[i] >> shift) & DIGIT_MASK;
}

// NOTE(Talkasi): Puts digit on the position, doesn't shift other bits.
void put_digit(bdouble_t *d, int digit_pos, int digit)
{
	int i = digit_pos / DIGITS_PER_LONG;
	int shift = BITS_IN_LONG - ((digit_pos + 1) % DIGITS_PER_LONG) * BITS_PER_DIGIT;

	d->mantissa[i] &= ~((long)DIGIT_MASK << shift);
	d->mantissa[i] |= (long)digit << shift;
}

int scanf_bdouble(bdouble_t *d)
{
	memset(d, 0, sizeof(*d));
	char c;

	int exponent_flag = 0;
	int point_flag = 0;

	if ((c = getchar()) == '\n' || c == EOF)
		return SCANF_ERR;

	d->sign = 1;
	if (c == '-')
		d->sign = -1;

	int i = 0;
	do {
		if (c == '.') {
			if (++point_flag > 1)
				return SCANF_ERR;
		} else if ('0' <= c && c <= '9') {
			if (!exponent_flag) {
				if (d->d_in_mantissa != 0 || (d->d_in_mantissa == 0 && c != '0'))
					put_digit(d, d->d_in_mantissa++, c - '0');
			} else
				d->exponent = d->exponent * 10 + (c - '0');
		} else if (c == 'e' || c == 'E') {
			if (++exponent_flag > 1)
				return SCANF_ERR;
		} else
			return SCANF_ERR;
	} while ((c = getchar()) != '\n' && c != EOF);

	return 0;
}

void printf_bdouble(bdouble_t *d)
{
	printf("%d.", get_digit(d, 0));
	for (int i = 1; i < DIGITS_PER_LONG * N_LONGS_IN_MANTISSA; ++i)
		printf("%d", get_digit(d, i));

	printf("e%c%02d\n", d->sign >= 0 ? '+' : '-', d->exponent);
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

void init_by_zeroes(bdouble_t *d, int i_from)
{
	for (int i = i_from; i < DIGITS_PER_LONG * N_LONGS_IN_MANTISSA; ++i)
		put_digit(d, i, 0);
}

void init_bdouble(bdouble_t *dst, bdouble_t *src, int i_from, int i_to)
{
	for (int i = i_from; i < i_to; ++i)
		put_digit(dst, i - i_from, get_digit(src, i));

	init_by_zeroes(dst, i_from);
	dst->d_in_mantissa = i_to - i_from - 1;
}

int delete_prev_zeroes(bdouble_t *d)
{
	int n_prev_zeros = 0;
	for (int i = 0; i < d->d_in_mantissa; ++i)
		if (get_digit(d, i) == 0)
			++n_prev_zeros;
		else
			break;

	init_bdouble(d, d, n_prev_zeros, d->d_in_mantissa);
	return n_prev_zeros;
}

// NOTE(Talkasi): Assumes that d1 >= d2, result is stored in d1.
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
	res->sign = (d1->sign == d2->sign) ? 1 : -1;
	int simple_divisor = get_digit(d2, 0);

	bdouble_t part_div = {};
	init_bdouble(&part_div, d1, 0, d2->d_in_mantissa);

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
