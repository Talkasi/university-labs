#include "check_tools.h"
#include <check.h>

int ck_lists_eq(node_t *head1, node_t *head2, comparator_t comparator)
{
    if (head1 == NULL)
    {
        if (head2 == NULL)
            return 1;
        else
            return 0;
    }

    node_t *cur_node1 = head1;
    node_t *cur_node2 = head2;

    while (cur_node1->next != NULL && cur_node2->next != NULL)
    {
        if (comparator(cur_node1->data, cur_node2->data) != 0)
            return 0;

        cur_node1 = cur_node1->next;
        cur_node2 = cur_node2->next;
    }

    if (cur_node1->next != NULL || cur_node2->next != NULL)
        return 0;
    else
        return 1;
}

void ck_car_cpy(car_t *dst, car_t *src)
{
    dst->model = src->model;
    dst->licence_number = src->licence_number;
    dst->year = src->year;
    dst->owners_name = src->owners_name;
}

void ck_cars_cpy(car_t dst[], car_t src[], size_t n)
{
    for (size_t i = 0; i < n; ++i)
        ck_car_cpy(&dst[i], &src[i]);
}

int ck_car_eq(car_t *car1, car_t *car2)
{
    if (car1->model == car2->model && car1->licence_number == car2->licence_number && car1->year == car2->year &&
        car1->owners_name == car2->owners_name)
        return 1;

    return 0;
}

int ck_cars_eq(car_t cars1[], car_t cars2[], size_t n)
{
    for (size_t i = 0; i < n; ++i)
        if (!ck_car_eq(&cars1[i], &cars2[i]))
            return 0;

    return 1;
}

int ck_cmp_ints(const void *e1, const void *e2)
{
    int int1 = *(int *)e1;
    int int2 = *(int *)e2;

    return int1 - int2;
}

int ck_cmp_chars(const void *e1, const void *e2)
{
    char char1 = *(char *)e1;
    char char2 = *(char *)e2;

    return char1 - char2;
}

int ck_cmp_doubles(const void *e1, const void *e2)
{
    double double1 = *(double *)e1;
    double double2 = *(double *)e2;

    if (fabs(double1 - double2) < EPS)
        return 0;
    else if (double1 < double2)
        return -1;
    else
        return 1;
}

node_t *ck_find_node_by_index(node_t *head, size_t n)
{
    node_t *cur_node = head;

    size_t i = 0;
    while (cur_node)
    {
        if (i++ == n)
            return cur_node;

        cur_node = cur_node->next;
    }

    return NULL;
}
