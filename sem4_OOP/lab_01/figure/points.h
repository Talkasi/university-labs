#ifndef POINTS_H
#define POINTS_H
#include <stdio.h>

typedef struct point_3D point_3D_t;
typedef struct points_3D points_3D_t;

struct point_3D
{
    double x;
    double y;
    double z;
};

struct points_3D
{
    point_3D_t *data;
    size_t n;
};

#endif // POINTS_H
