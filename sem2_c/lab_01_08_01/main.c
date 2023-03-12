#include <inttypes.h>
#include <limits.h>
#include <stdio.h>

#define N_BYTES (int)sizeof(uint32_t)

void print_bin_representation(uint32_t integer);

int main(void)
{
    unsigned char byte;
    int shifter = CHAR_BIT * (N_BYTES - 1);
    uint32_t integer = 0;

    for (int i = 0; i < N_BYTES; ++i)
    {
        printf("Enter byte: ");
        if (scanf("%hhu", &byte) != 1)
        {
            printf("Error: Input error.\n");
            return 1;
        }

        integer |= ((uint32_t)byte << shifter);
        shifter -= CHAR_BIT;
    }

    printf("Result: ");
    print_bin_representation(integer);

    for (int i = 0; i < N_BYTES; ++i)
    {
        printf(" %lu", (integer & 0xFFUL << CHAR_BIT * (N_BYTES - i - 1)) >> CHAR_BIT * (N_BYTES - i - 1));
    }
    return 0;
}

void print_bin_representation(uint32_t integer)
{
    for (int i = N_BYTES * CHAR_BIT - 1; i >= 0; --i)
        printf("%d", (integer & (1UL << i)) != 0);
}
