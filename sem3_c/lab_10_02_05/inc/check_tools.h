#ifndef CHECK_TOOLS_H
#define CHECK_TOOLS_H
#include "list.h"
#include <stdio.h>

#define EPS 10e-9
typedef int (*comparator_t)(const void *, const void *);

void ck_lists_eq(node_t *head1, node_t *head2);
int ck_cmp_part_strs(const void *e1, const void *e2);
int ck_cmp_chars(const void *e1, const void *e2);
int ck_cmp_ints(const void *e1, const void *e2);
int ck_cmp_doubles(const void *e1, const void *e2);
node_t *ck_find_node_by_index(node_t *head, size_t n);

#endif