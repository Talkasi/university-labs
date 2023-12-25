#include "check_tools.h"
#include <check.h>

void ck_lists_eq(node_t *head1, node_t *head2)
{
    if (head1 == NULL)
    {
        ck_assert_mem_eq(&head1, &head2, sizeof(node_t *));
        return;
    }

    node_t *cur_node1 = head1;
    node_t *cur_node2 = head2;

    while (cur_node1->next != NULL && cur_node2->next != NULL)
    {
        ck_assert_mem_eq(&cur_node1->data, &cur_node2->data, PART_LEN);

        cur_node1 = cur_node1->next;
        cur_node2 = cur_node2->next;
    }

    ck_assert_mem_eq(&cur_node1->next, &cur_node2->next, sizeof(node_t *));
}

int ck_cmp_part_strs(const void *e1, const void *e2)
{
    return memcmp(e1, e2, PART_LEN * sizeof(char));
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
