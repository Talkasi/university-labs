#ifndef EDGES_H
#define EDGES_H
#include <stdio.h>

typedef struct edge edge_t;
typedef struct edges edges_t;

struct edge
{
    size_t first;
    size_t second;
};

struct edges
{
    edge_t *data;
    size_t n;
};

#endif // EDGES_H
