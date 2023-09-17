#include "my_big_types.h"
#include <ctype.h>
#include <stdio.h>
#include <string.h>

long del_useless_zeroes(char *arr, int *arr_len) {
    long new_len = 0;
    int leading_zeroes = 1;
    for (long i = 0; i < *arr_len; ++i) {
        if (arr[i] != 0)
            leading_zeroes = 0;
        if (!leading_zeroes)
            arr[new_len++] = arr[i];
    }

    long zeroes_before = *arr_len - new_len;
    for (long i = new_len - 1; i > 0; --i)
        if (arr[i] == 0)
            new_len--;
        else
            break;

    *arr_len = new_len;
    return zeroes_before;
}

int str_to_bdouble(char *number, struct my_big_double *n) {
    int cur_i = 0;
    n->fraction_sign = +1;
    int were_sign = 0;
    if (number[0] == '-') {
        n->fraction_sign = -1;
        ++cur_i;
        ++were_sign;
    } else if (number[0] == '+') {
        ++cur_i;
        ++were_sign;
    }

    n->fraction_len = 0;
    while (isdigit(number[cur_i])) {
        n->fraction[n->fraction_len++] = number[cur_i++] - '0';
        if (n->fraction_len > NDIGITS_IN_FRACTION)
            return TOO_BIG_FRACT_ERR;
    }

    long point = strlen(number) - were_sign;
    if (number[cur_i] == '.') {
        cur_i++;
        point = n->fraction_len;
    }

    while (isdigit(number[cur_i])) {
        n->fraction[n->fraction_len++] = number[cur_i++] - '0';
        if (n->fraction_len > NDIGITS_IN_FRACTION)
            return TOO_BIG_FRACT_ERR;
    }

    int before = del_useless_zeroes(n->fraction, &n->fraction_len);
    n->exponent = 0;
    int exp_sign = 1;
    if ((number[cur_i] == 'e' || number[cur_i] == 'E') && cur_i > 0 && (isdigit(number[cur_i - 1]) || number[cur_i - 1] == '.')) {
        if (cur_i < point)
            point = cur_i;
        cur_i++;

        if (number[cur_i] == '-') {
            cur_i++;
            exp_sign = -1;
        } else if (number[cur_i] == '+')
            cur_i++;

        int i_exp = 0;
        while (isdigit(number[cur_i])) {
            n->exponent = n->exponent * 10 + (number[cur_i++] - '0');
            if (i_exp >= NDIGITS_IN_EXP)
                return TOO_BIG_EXP_ERR;
            ++i_exp;
        }
    }

    n->exponent = n->exponent * exp_sign + (point - before);
    return number[cur_i] != '\0';
}

int str_to_bint(char *number, struct my_big_int *n) {
    int cur_i = 0;

    n->sign = +1;
    if (number[cur_i] == '-') {
        n->sign = -1;
        cur_i++;
    } else if (number[cur_i] == '+')
        cur_i++;

    n->digits_len = 0;
    while (isdigit(number[cur_i])) {
        n->digits[n->digits_len++] = number[cur_i++] - '0';
        if (n->digits_len > NDIGITS_IN_BINT)
            return TOO_BIG_INT_ERR;
    }

    long end = n->digits_len - 1;
    for (long i = NDIGITS_IN_BINT_x2 - 1; i >= NDIGITS_IN_BINT_x2 - n->digits_len; --i)
        n->digits[i] = n->digits[end--];

    // Delete useless zeroes
    for (long i = NDIGITS_IN_BINT_x2 - n->digits_len; i < NDIGITS_IN_BINT_x2 - 1; ++i)
        if (n->digits[i] == 0)
            --n->digits_len;
        else
            break;

    return number[cur_i] != '\0';
}

void shift_round_bint(char *digits, char first_digit, int len) {
    int to_round = 1;
    int carry = 0;
    for (long i = NDIGITS_IN_BINT_x2 - 1; i > NDIGITS_IN_BINT_x2 - len; --i) {
        if (digits[i] >= 5 && to_round || !to_round) {
            digits[i] = digits[i - 1] + carry + to_round;
            to_round = 0;
            if (digits[i] > 9) {
                carry = 1;
                digits[i] = digits[i] % 10;
            } else
                carry = 0;
        } else
            digits[i] = digits[i - 1] + carry;
    }

    digits[len - 1] = first_digit;
}

void round_bdouble(char *digits, char last_digit, int len) {
    if (last_digit < 5)
        return;

    int to_round = 1;
    int carry = 0;
    for (long i = len - 1; i >= 0; --i) {
        if (digits[i] >= 5 && to_round || !to_round) {
            digits[i] = digits[i] + carry + to_round;
            to_round = 0;
            if (digits[i] > 9) {
                carry = 1;
                digits[i] = digits[i] % 10;
            } else
                carry = 0;
        } else
            digits[i] = digits[i - 1] + carry;
    }

    if (carry != 0) {
        for (long i = 1; i < len; ++i)
            digits[i] = digits[i - 1];
        digits[0] = carry;
    }
}

void mul_int_on_bint(int n, struct my_big_int *bint) {
    int tmp, carry = 0;
    long i;
    for (i = NDIGITS_IN_BINT_x2 - 1; i >= NDIGITS_IN_BINT_x2 - bint->digits_len; --i) {
        tmp = bint->digits[i] * n + carry;
        bint->digits[i] = tmp % 10;
        carry = tmp / 10;
    }

    if (carry != 0) {
        if (i >= 0) {
            ++bint->digits_len;
            bint->digits[i] = carry;
        } else
            shift_round_bint(bint->digits, carry, bint->digits_len);
    }
}

int bint_cmp(struct my_big_int *bi1, struct my_big_int *bi2) {
    if (bi1->digits_len > bi2->digits_len)
        return 1;
    if (bi1->digits_len < bi2->digits_len)
        return -1;

    for (long i = NDIGITS_IN_BINT_x2 - bi1->digits_len; i < NDIGITS_IN_BINT_x2; ++i)
        if (bi1->digits[i] > bi2->digits[i])
            return 1;
        else if (bi1->digits[i] < bi2->digits[i])
            return -1;

    return 0;
}

int sub_bints(struct my_big_int *bigger, struct my_big_int *smaller) {
    int taken = 0;
    long i;
    for (i = NDIGITS_IN_BINT_x2 - 1; i >= NDIGITS_IN_BINT_x2 - smaller->digits_len; --i) {
        if (bigger->digits[i] >= smaller->digits[i] + taken) {
            bigger->digits[i] = bigger->digits[i] - smaller->digits[i] - taken;
            taken = 0;
        } else {
            bigger->digits[i] = 10 + bigger->digits[i] - smaller->digits[i] - taken;
            taken = 1;
        }
    }

    bigger->digits[i] -= taken;
    // Delete useless zeroes
    int n_deleted = 0;
    for (i = NDIGITS_IN_BINT_x2 - bigger->digits_len; i < NDIGITS_IN_BINT_x2; ++i)
        if (bigger->digits[i] == 0) {
            --bigger->digits_len;
            ++n_deleted;
        } else
            break;

    return n_deleted;
}

int power(int base, int n) {
    int ans = 1;
    for (int i = 0; i < n; ++i)
        ans *= base;
    return ans;
}

int div_bdouble_by_bint(struct my_big_double *dividend, struct my_big_int *divisor, struct my_big_double *quotient) {
    quotient->fraction_sign = dividend->fraction_sign == divisor->sign ? 1 : -1;
    quotient->fraction_len = 0;
    quotient->exponent = dividend->exponent + 1;

    int n_shift = 0;
    for (long i = NDIGITS_IN_BINT_x2 - 1; i > NDIGITS_IN_BINT_x2 - divisor->digits_len; --i) {
        if (divisor->digits[i] == 0) {
            --quotient->exponent;
            ++n_shift;
        } else
            break;
    }

    divisor->digits_len -= n_shift;
    for (long i = NDIGITS_IN_BINT_x2 - 1; i >= NDIGITS_IN_BINT_x2 - divisor->digits_len; --i) {
        divisor->digits[i] = divisor->digits[i - n_shift];
    }

    // Part dividend saving
    struct my_big_int part_dividend;
    memset(&part_dividend, 0, sizeof(part_dividend));
    part_dividend.digits_len = divisor->digits_len;
    part_dividend.sign = +1;
    for (long i = NDIGITS_IN_BINT_x2 - part_dividend.digits_len; i < NDIGITS_IN_BINT_x2; ++i) {
        if ((i + part_dividend.digits_len) - NDIGITS_IN_BINT_x2 < dividend->fraction_len)
            part_dividend.digits[i] = dividend->fraction[(i + part_dividend.digits_len) - NDIGITS_IN_BINT_x2];
        else
            part_dividend.digits[i] = 0;
    }

    // Check if part dividend is less than divisor
    if (bint_cmp(divisor, &part_dividend) > 0) {
        part_dividend.digits_len = divisor->digits_len + 1;
        for (long i = NDIGITS_IN_BINT_x2 - part_dividend.digits_len; i < NDIGITS_IN_BINT_x2 - 1; ++i)
            part_dividend.digits[i] = part_dividend.digits[i + 1];

        if (part_dividend.digits_len > dividend->fraction_len)
            part_dividend.digits[NDIGITS_IN_BINT_x2 - 1] = 0;
        else
            part_dividend.digits[NDIGITS_IN_BINT_x2 - 1] = dividend->fraction[part_dividend.digits_len - 1];
    }

    long were_digits = part_dividend.digits_len;
    int tmp_quotient;
    while (1) {
        if (part_dividend.digits_len == divisor->digits_len)
            tmp_quotient = part_dividend.digits[NDIGITS_IN_BINT_x2 - part_dividend.digits_len] /
                           divisor->digits[NDIGITS_IN_BINT_x2 - divisor->digits_len];
        else
            tmp_quotient = (part_dividend.digits[NDIGITS_IN_BINT_x2 - part_dividend.digits_len] * 10 +
                            part_dividend.digits[NDIGITS_IN_BINT_x2 - part_dividend.digits_len + 1]) /
                           divisor->digits[NDIGITS_IN_BINT_x2 - divisor->digits_len];

        struct my_big_int tmp = *divisor;
        mul_int_on_bint(tmp_quotient, &tmp);

        while (bint_cmp(&tmp, &part_dividend) > 0) {
            --tmp_quotient;
            tmp = *divisor;
            mul_int_on_bint(tmp_quotient, &tmp);
        }

        int z_deleted = sub_bints(&part_dividend, &tmp);
        if (quotient->fraction_len == 0)
            quotient->exponent -= z_deleted;

        if (quotient->fraction_len + 1 > NDIGITS_IN_FRACTION)
            break;
        quotient->fraction[quotient->fraction_len++] = tmp_quotient;
        if (part_dividend.digits_len == 0 && were_digits >= dividend->fraction_len) {
            tmp_quotient = 0;
            break;
        }

        int counter = -1;
        do {
            for (long i = NDIGITS_IN_BINT_x2 - part_dividend.digits_len; i < NDIGITS_IN_BINT_x2; ++i)
                part_dividend.digits[i - 1] = part_dividend.digits[i];

            ++part_dividend.digits_len;
            ++were_digits;
            if (were_digits > dividend->fraction_len)
                part_dividend.digits[NDIGITS_IN_BINT_x2 - 1] = 0;
            else
                part_dividend.digits[NDIGITS_IN_BINT_x2 - 1] = dividend->fraction[were_digits - 1];
            ++counter;
        } while (part_dividend.digits_len < divisor->digits_len);

        while (counter > 0) {
            if (quotient->fraction_len + 1 > NDIGITS_IN_FRACTION) {
                tmp_quotient = 0;
                break;
            }
            quotient->fraction[quotient->fraction_len++] = 0;
            --counter;
        }

        if (quotient->fraction_len + 1 > NDIGITS_IN_FRACTION)
            break;

        if (bint_cmp(divisor, &part_dividend) > 0) {
            ++part_dividend.digits_len;
            for (long i = NDIGITS_IN_BINT_x2 - part_dividend.digits_len; i < NDIGITS_IN_BINT_x2 - 1; ++i)
                part_dividend.digits[i] = part_dividend.digits[i + 1];

            if (were_digits > dividend->fraction_len)
                part_dividend.digits[NDIGITS_IN_BINT_x2 - 1] = 0;
            else
                part_dividend.digits[NDIGITS_IN_BINT_x2 - 1] = dividend->fraction[were_digits - 1];
        }
    }

    if (quotient->fraction_len + 1 > NDIGITS_IN_FRACTION)
        round_bdouble(quotient->fraction, tmp_quotient, quotient->fraction_len);

    for (long i = quotient->fraction_len - 1; i > 0; --i)
        if (quotient->fraction[i] == 0) {
            --quotient->fraction_len;
        } else
            break;

    if (quotient->exponent / power(10, NDIGITS_IN_EXP) != 0)
        return OWERFLOW_ERROR;
    return 0;
}

int is_bint_zero(struct my_big_int *bint) {
    if (bint->digits_len == 1 && bint->digits[NDIGITS_IN_BINT_x2 - 1] == 0)
        return 1;

    return 0;
}

void print_bdouble(struct my_big_double *n) {
    if (n->fraction_len == 1 && n->fraction[0] == 0)
        printf("+0.E+0\n");
    else {
        printf("%c0.", n->fraction_sign > 0 ? '+' : '-');
        for (int i = 0; i < n->fraction_len; ++i)
            printf("%d", n->fraction[i]);
        printf("E%s%ld\n", n->exponent >= 0 ? "+" : "", n->exponent);
    }
}

void print_bint(struct my_big_int *n) {
    printf("%c", n->sign > 0 ? '+' : '-');
    for (int i = NDIGITS_IN_BINT_x2 - n->digits_len; i < NDIGITS_IN_BINT_x2; ++i)
        printf("%d", n->digits[i]);
    printf("\n");
}
