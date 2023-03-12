#include <math.h>
#include <stdio.h>

#define EPS 1e-8
#define ON_LINE_SEGMENT 1
#define OUT_OF_LINE_SEGMENT 0

int main(void)
{
    double xq, yq;
    double xr, yr;
    double xp, yp;
    double tmp;

    printf("Enter x, y of the point q: ");
    if (scanf("%lf %lf", &xq, &yq) != 2)
    {
        printf("Input error.");
        return 1;
    }

    printf("Enter x, y of the point r: ");
    if (scanf("%lf %lf", &xr, &yr) != 2)
    {
        printf("Input error.");
        return 1;
    }

    /* Check if there is a line segment */
    if (fabs(xr - xq) < EPS && fabs(yr - yq) < EPS)
    {
        printf("This is not a line segment.");
        return 1;
    }

    printf("Enter x, y of the point p: ");
    if (scanf("%lf %lf", &xp, &yp) != 2)
    {
        printf("Input error.");
        return 1;
    }

    if (yq > yr)
    {
        tmp = yr;
        yr = yq;
        yq = tmp;

        tmp = xr;
        xr = xq;
        xq = tmp;
    }

    /* Check if point is on the line segment */
    if ((yp - yq) * (xq - xr) - (yp - yr) * (xp - xq) < EPS && yp <= yr && yp >= yq)
        printf("Resulting status: %d", ON_LINE_SEGMENT);
    else
        printf("Resulting status: %d", OUT_OF_LINE_SEGMENT);

    return 0;
}
