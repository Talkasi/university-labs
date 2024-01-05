#ifndef BIG_NUMS_H
#define BIG_NUMS_H

#define SCANF_ERR 1

#define DIGIT_MASK 15 // 0b1111
#define BITS_PER_DIGIT 4
#define N_SIGNIFICANTS 32
#define BITS_IN_LONG (sizeof(long) * 8)
#define DIGITS_PER_LONG (BITS_IN_LONG / BITS_PER_DIGIT)
#define N_LONGS_IN_MANTISSA (BITS_IN_LONG / N_SIGNIFICANTS)


typedef struct bdouble {
	long mantissa[N_LONGS_IN_MANTISSA];
	int d_in_mantissa;
	int exponent;
	char sign;
} bdouble_t;

int scanf_bdouble(bdouble_t *d);
void printf_bdouble(bdouble_t *d);

int mul_bdouble(bdouble_t *res, bdouble_t *d, int num);
int div_bdoubles(bdouble_t *res, bdouble_t *d1, bdouble_t *d2);

#endif