#include <stdio.h>
#include <math.h>

int main()
{
    double xq, yq;
    double xr, yr;
    double xp, yp;
    double eps = 1e-8, folder;

    printf("Enter x of the point q: ");
    if (scanf("%lf", &xq) != 1)
    {
        printf("Input error");
        return 1;
    }

    printf("Enter y of the point q: ");
    if (scanf("%lf", &yq) != 1)
    {
        printf("Input error.");
        return 1;
    }

    printf("Enter x of the point r: ");
    if (scanf("%lf", &xr) != 1)
    {
        printf("Input error.");
        return 1;
    }

    printf("Enter y of the point r: ");
    if (scanf("%lf", &yr) != 1)
    {
        printf("Input error.");
        return 1;
    }

    if (fabs(xr - xq) < eps && fabs(yr - yq) < eps)
    {
        printf("This is not a line segment.");
        return 1;
    }

    printf("Enter x of the point p: ");
    if (scanf("%lf", &xp) != 1)
    {
        printf("Input error.");
        return 1;
    }

    printf("Enter y of the point p: ");
    if (scanf("%lf", &yp) != 1)
    {
        printf("Input error.");
        return 1;
    }

    if (yq > yr)
    {
        folder = yr;
        yr = yq;
        yq = folder;

        folder = xr;
        xr = xq;
        xq = folder;
    }

    if ((yp - yq) * (xq - xr) - (yp - yr) * (xp - xq) < eps && yp <= yr && yp >= yq)
        printf("1");
    else
        printf("0");

    return 0;
}
