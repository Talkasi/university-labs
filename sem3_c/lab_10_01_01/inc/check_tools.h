#ifndef CHECK_TOOLS_H
#define CHECK_TOOLS_H
#include "list.h"
#include "stdio.h"

#define EPS 10e-9

int ck_lists_eq(node_t *head1, node_t *head2, comparator_t comparator);
void ck_car_cpy(car_t *dst, car_t *src);
void ck_cars_cpy(car_t dst[], car_t src[], size_t n);
int ck_car_eq(car_t *car1, car_t *car2);
int ck_cars_eq(car_t cars1[], car_t cars2[], size_t n);
int ck_cmp_chars(const void *e1, const void *e2);
int ck_cmp_ints(const void *e1, const void *e2);
int ck_cmp_doubles(const void *e1, const void *e2);
node_t *ck_find_node_by_index(node_t *head, size_t n);

#endif