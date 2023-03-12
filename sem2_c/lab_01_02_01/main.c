#include <math.h>
#include <stdio.h>

#define PI acos(-1.0)

int main(void)
{
    double a, b, angle_val;
    double s, side;
    double tmp;

    printf("Enter value of the first base of the trapezoid: ");
    if (scanf("%lf", &a) != 1 || a <= 0.0)
    {
        printf("Input error. Value should be bigger than zero.\n");
        return 1;
    }

    printf("Enter value of the second base of the trapezoid: ");
    if (scanf("%lf", &b) != 1 || b <= 0.0)
    {
        printf("Input error. Value should be bigger than zero.\n");
        return 1;
    }

    printf("Enter value of the angle: ");
    if (scanf("%lf", &angle_val) != 1 || angle_val <= 0.0 || angle_val >= 90.0)
    {
        printf("Input error. Value should be bigger than zero.\n");
        return 1;
    }

    if (a > b)
    {
        tmp = a;
        a = b;
        b = tmp;
    }

    side = (b - a) / 2.0 / cos(angle_val * PI / 180.0);
    if (a + side + side <= b || b + side + side <= a || a + b + side <= side)
    {
        printf("The trapezoid with this parameters does not exist.\n");
        return 1;
    }

    s = tan(angle_val * PI / 180.0) * (b - a) * (a + b) / 4.0;

    printf("The answer is: %.6lf\n", s);
    return 0;
}
