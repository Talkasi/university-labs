#include "big_nums.h"
#include <stdio.h>
#include <string.h>
#include <assert.h>

int get_digit(bdouble_t *d, int digit_pos)
{
	int i = digit_pos / DIGITS_PER_LONG;
	int shift = BITS_IN_LONG - ((digit_pos + 1) % DIGITS_PER_LONG) * BITS_PER_DIGIT;
	return (d->mantissa[i] >> shift) & DIGIT_MASK;
}

// NOTE(Talkasi): Puts digit on the position, doesn't shift other bits.
void put_digit(bdouble_t *d, int digit_pos, int digit)
{
	assert(digit >= 0 && digit <= 9);
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
	} while ((c = getchar()) != '\n' && c != EOF && c != ' ');

	return 0;
}

void printf_bdouble(bdouble_t *d)
{
	if (d->sign < 0)
		printf("-");
	printf("%d.", get_digit(d, 0));
	for (int i = 1; i < d->d_in_mantissa; ++i)
		printf("%d", get_digit(d, i));

	printf("e%+03d", d->exponent);
	printf("\n");
}

void printf_bdouble_mantissa(bdouble_t *d)
{
	for (int i = 0; i < d->d_in_mantissa; ++i)
		printf("%d", get_digit(d, i));
	printf("\n");
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
	for (int i = i_from; i < N_SIGNIFICANTS; ++i)
		put_digit(d, i, 0);
}

void init_bdouble(bdouble_t *dst, bdouble_t *src, int i_from, int i_to)
{
	for (int i = i_from; i < i_to; ++i)
		put_digit(dst, i - i_from, get_digit(src, i));

	dst->d_in_mantissa = i_to - i_from;
	init_by_zeroes(dst, dst->d_in_mantissa);
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
		int second_digit = (i - d2_shifter) >= 0 ? get_digit(d2, i - d2_shifter) : 0;
		int new_digit = get_digit(d1, i) - second_digit - carry;
		if (new_digit < 0) {
			carry = 1;
			new_digit += 10;
		} else
			carry = 0;

		put_digit(d1, i, new_digit % 10);
	}

	return delete_prev_zeroes(d1);
}

int mul_bdouble(bdouble_t *res, bdouble_t *d, int num)
{
	assert(d->d_in_mantissa <= N_SIGNIFICANTS);
	memset(res, 0, sizeof(*res));
	if (num == 0)
		return 0;

	int carry = 0;
	int new_digit;
	res->d_in_mantissa = d->d_in_mantissa;
	for (int i = d->d_in_mantissa - 1; i >= 0; --i) {
		new_digit = get_digit(d, i) * num + carry;
		carry = new_digit / 10;
		put_digit(res, i, new_digit % 10);
	}

	assert(carry >= 0 && carry < 10);
	if (carry != 0) {
		if (res->d_in_mantissa < N_SIGNIFICANTS) {
			for (int i = res->d_in_mantissa; i > 0; --i)
				put_digit(res, i, get_digit(res, i - 1));

			put_digit(res, 0, carry);
			++res->d_in_mantissa;
		} else {
			int round = get_digit(res, res->d_in_mantissa - 1) >= 5;
			for (int i = res->d_in_mantissa - 1; i > 0; --i) {
				new_digit = get_digit(res, i - 1) + round;
				round = new_digit > 9;
				put_digit(res, i, new_digit % 10);
			}

			assert(carry + round < 10);
			put_digit(res, 0, carry + round);
		}
	}

	return 0;
}

// int round_bdouble(bdouble_t *res, int round) {
// 	if (round) {
// 		for (int i = res->d_in_mantissa - 1; i >= 0; --i) {
// 			new_digit = get_digit(res, i) + round;
// 			round = new_digit > 9;
// 			put_digit(res, i, new_digit % 10);
// 		}
// 	}
// }

int div_bdoubles(bdouble_t *res, bdouble_t *d1, bdouble_t *d2)
{
	memset(res, 0, sizeof(*res));
	res->sign = (d1->sign == d2->sign) ? 1 : -1;
	res->exponent = d1->exponent - d2->exponent;
	if (res->sign < 0)
		res->exponent -= 1;

	bdouble_t part_div = {};
	init_bdouble(&part_div, d1, 0, d2->d_in_mantissa);

	int next_d1_digit_i = d2->d_in_mantissa;
	bdouble_t tmp_mul_res = {};
	int new_digit;
	int result_digit;
	int first_flag;
	do {
		first_flag = 1;
		while (cmp_bdoubles(&part_div, d2) < 0) {
			if (next_d1_digit_i >= d1->d_in_mantissa && part_div.d_in_mantissa == 0)
				return 0;

			new_digit = (next_d1_digit_i < d1->d_in_mantissa) ? get_digit(d1, next_d1_digit_i++) : 0;
			if (!(part_div.d_in_mantissa == 0 && new_digit == 0))
				put_digit(&part_div, part_div.d_in_mantissa++, new_digit);
			if (!first_flag && 0 < res->d_in_mantissa && res->d_in_mantissa < N_SIGNIFICANTS)
				put_digit(res, res->d_in_mantissa++, 0);
			first_flag = 0;
		}

		result_digit = 9;
		mul_bdouble(&tmp_mul_res, d2, result_digit);
		while (cmp_bdoubles(&tmp_mul_res, &part_div) > 0)
			mul_bdouble(&tmp_mul_res, d2, --result_digit);

		sub_bdoubles(&part_div, &tmp_mul_res);

		assert(result_digit > 0);
		assert(result_digit <= 9);
		assert(cmp_bdoubles(&part_div, d2) < 0);

		if (res->d_in_mantissa < N_SIGNIFICANTS && !(res->d_in_mantissa == 0 && result_digit == 0))
			put_digit(res, res->d_in_mantissa++, result_digit);
	} while ((next_d1_digit_i < d1->d_in_mantissa || part_div.d_in_mantissa > 0) && res->d_in_mantissa < N_SIGNIFICANTS);

	return 0;
}
