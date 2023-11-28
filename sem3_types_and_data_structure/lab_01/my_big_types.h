#ifndef MY_BIG_TYPES_H
#define MY_BIG_TYPES_H
#include <stdio.h>

#define NDIGITS_IN_FRACTION 35
#define NDIGITS_IN_BINT 35
#define NDIGITS_IN_EXP 5

#define NDIGITS_IN_FRACTION_x2 NDIGITS_IN_FRACTION * 2
#define NDIGITS_IN_BINT_x2 NDIGITS_IN_BINT * 2

#define TOO_BIG_FRACT_ERR -10
#define TOO_BIG_EXP_ERR -11
#define TOO_BIG_INT_ERR -12
#define OWERFLOW_ERROR -13

struct my_big_double {
    char fraction_sign;
    int fraction_len;
    char fraction[NDIGITS_IN_FRACTION_x2];
    long exponent;
};

struct my_big_int {
    char sign;
    int digits_len;
    char digits[NDIGITS_IN_BINT_x2];
};

int str_to_bdouble(char *number, struct my_big_double *n);
int str_to_bint(char *number, struct  my_big_int *n);

int div_bdouble_by_bint(struct my_big_double *dividend, struct my_big_int *divisor, struct my_big_double *quotient);

void print_bdouble(struct my_big_double *n);
void print_bint(struct my_big_int *n);

int is_bint_zero(struct my_big_int *bint);

#endif
