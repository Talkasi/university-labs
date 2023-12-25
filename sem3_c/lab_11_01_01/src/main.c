#include "my_snprintf.h"
#include <limits.h>
#include <stdio.h>

#define TEST_BUFFER_LEN 12

int main()
{
    char test_buffer[TEST_BUFFER_LEN];
    char result_buffer[TEST_BUFFER_LEN];
    char format[] = "%.0d";

    int arg1 = 1;

    int test_rc = my_snprintf(test_buffer, 0, format, arg1);
    int result_rc = snprintf(result_buffer, 0, format, arg1);

    printf("%s|\n%s|\n", test_buffer, result_buffer);
}
