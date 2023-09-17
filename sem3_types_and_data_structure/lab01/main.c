#include "my_big_types.h"
#include <stdio.h>
#include <string.h>

#define MAX_STR_LEN (45)

void bint_description();
void breal_description();
size_t fread_line(FILE *f, char *s, size_t max_len);
void print_scale(int offset, long len);

#define DIVIDEND_TXT "Enter dividend, big real number: "
#define DIVISOR_TXT "Enter divisor, big integer: "
int main() {
    printf("This is the program which divides big real number on a big integer.\n\n");
    breal_description();
    bint_description();

    char string[MAX_STR_LEN];

    struct my_big_double dividend;
    struct my_big_int divisor;
    struct my_big_double quotient;

    memset(&dividend, 0, sizeof(dividend));
    memset(&divisor, 0, sizeof(divisor));
    memset(&quotient, 0, sizeof(quotient));

    print_scale(strlen(DIVIDEND_TXT), NDIGITS_IN_FRACTION);
    printf(DIVIDEND_TXT);
    int rc;
    while (fread_line(stdin, string, MAX_STR_LEN) == 0 || (rc = str_to_bdouble(string, &dividend))) {
        printf("> Incorrect dividend.\n");
        switch (rc) {
            case (TOO_BIG_EXP_ERR):
                printf("Exponent is too big. Number of digits in it must be less than %d\n", NDIGITS_IN_EXP);
                break;
            case (TOO_BIG_FRACT_ERR):
                printf("Factorial is too big. Number of digits in it must be less than %d\n", NDIGITS_IN_FRACTION);
                break;
            default:
                printf("Not a big real number.\n");
                breal_description();
                break;
        }
        printf("Please, try again. Enter dividend, big real number:\n");
        print_scale(0, NDIGITS_IN_FRACTION);
    }

    print_scale(strlen(DIVISOR_TXT), NDIGITS_IN_BINT);
    printf(DIVISOR_TXT);
    while (fread_line(stdin, string, MAX_STR_LEN) == 0 || (rc = str_to_bint(string, &divisor)) || is_bint_zero(&divisor)) {
        printf("> Incorrect divisor.\n");
        if (is_bint_zero(&divisor))
            printf("> It is impossible to divide by 0.\n");
        else {
            if (rc == TOO_BIG_INT_ERR)
                printf("Number of digits is too big. Should be less than %d\n", NDIGITS_IN_BINT);
            else
                bint_description();
        }
        printf("Please, try again. Enter divisor, big integer:\n");
        print_scale(0, NDIGITS_IN_BINT);
    }

    rc = div_bdouble_by_bint(&dividend, &divisor, &quotient);
    if (rc == OWERFLOW_ERROR) {
        printf("Overflow error.\n");
        return OWERFLOW_ERROR;
    }

    print_scale(10, quotient.fraction_len + 2);
    printf("Quotient: ");
    print_bdouble(&quotient);
    return 0;
}

void breal_description() {
    printf(">>> Big real number is a number with at most %d digits in fraction part and\n"
           "at most %d digits in exponent. If sign is not specified, it is '+' by default.\n"
           "Leading zeroes are counted as digits. There shouldn't be any spaces in the number.\n\n",
           NDIGITS_IN_FRACTION, NDIGITS_IN_EXP);
}

void bint_description() {
    printf(">>> Big integer is a number with at most %d digits. If sign is not specified,\n"
           "it is '+' by default. Leading zeroes are counted as digits.\n\n",
           NDIGITS_IN_BINT);
}

size_t fread_line(FILE *f, char *s, size_t max_len) {
    char tmp[MAX_STR_LEN];
    if (max_len > MAX_STR_LEN)
        return 0;

    if (fgets(tmp, MAX_STR_LEN, f) == NULL)
        return 0;

    size_t len_tmp = strlen(tmp);
    if (tmp[len_tmp - 1] != '\n')
        return 0;

    tmp[--len_tmp] = '\0';
    if (len_tmp >= max_len)
        return 0;

    strcpy(s, tmp);
    return len_tmp;
}

void print_scale(int offset, long len) {
    for (int i = 0; i < offset; ++i)
        printf(" ");

    printf("S");
    for (long i = 1; i <= len; ++i)
        if (i % 5 == 0)
            printf("%ld", i / 5);
        else
            printf("-");

    printf("|\n");
}
