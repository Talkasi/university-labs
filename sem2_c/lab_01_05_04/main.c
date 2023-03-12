#include <stdio.h>

void print_prime_factors(int n);

int main(void)
{
    int n;

    printf("Enter number to work with: ");
    if (scanf("%d", &n) != 1 || n <= 0)
    {
        printf("Input error.");
        return 1;
    }

    if (n > 1)
    {
        printf("Answer:");
        print_prime_factors(n);
    }

    return 0;
}

void print_prime_factors(int n)
{
    int border;

    border = n / 2 + 1;
    for (int i = 2; i <= border && n > 1; ++i)
        while (n % i == 0)
        {
            printf(" %d", i);
            n = n / i;
        }

    if (n != 1)
        printf(" %d", n);
}
