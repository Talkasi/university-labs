#include <math.h>
#include <stdio.h>

int main(void)
{
    double x;
    double g = 0.0;
    double n = 1.0;

    printf("Enter first number: ");
    if (scanf("%lf", &x) != 1 || x < 0.0)
    {
        printf("Input error.\n");
        return 1;
    }

    while (x >= 0.0)
    {
        g += sqrt(x / n);
        ++n;
        if (scanf("%lf", &x) != 1)
        {
            printf("Input error.\n");
            return 1;
        }
    }

    g = sin(g);

    printf("%.6lf", g);
    return 0;
}
