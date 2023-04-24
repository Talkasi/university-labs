#include <math.h>
#include <stdio.h>

#define INPUT_X_ERROR 1
#define INPUT_EPS_ERROR 2

double my_sum(double x, double eps);

int main(void)
{
    double x, eps;

    printf("Enter x: ");
    if (scanf("%lf", &x) != 1)
    {
        printf("Input x error.\n");
        return INPUT_X_ERROR;
    }

    printf("Enter eps: ");
    if (scanf("%lf", &eps) != 1 || eps <= 0)
    {
        printf("Input eps error.\n");
        return INPUT_EPS_ERROR;
    }

    double sum = my_sum(x, eps);

    printf("Sum: %e\n", sum);
    printf("F(x): %+.5lf\n", cos(asin(x)));

    return 0;
}

double my_sum(double x, double eps)
{
    int i = 3;
    double a_j = -x / (2 * 5 * 4 * 3 * 2 - 4 * 3 * 2);
    double sum = 0;

    while (fabs(a_j) >= eps)
    {
        sum += a_j;
        ++i;
        a_j *= x * (2.0 * i + 1.0) / (i + 1.0) / (2.0 * i + 3.0);
    }

    return sum;
}
