#ifndef BIG_NUMS_H
#define BIG_NUMS_H

#define DIGIT_MASK 0b1111
#define BITS_PER_DIGIT 4
#define N_SIGNIFICANTS 32
#define BITS_IN_LONG (sizeof(long) * 8)
#define DIGITS_PER_LONG (BITS_IN_LONG / BITS_PER_DIGIT)
#define N_LONGS_IN_MANTISSA 4

typedef struct bdouble {
	long mantissa[N_LONGS_IN_MANTISSA];
	int d_in_mantissa;
	int exponent;
	char sign;
} bdouble_t;

#endif