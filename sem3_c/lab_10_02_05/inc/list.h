#ifndef LIST_H
#define LIST_H
#include <stdio.h>

#define PART_LEN 4
#define MAX_STR_LEN 128

enum errs
{
    NOT_FOUND = -10,
    ALLOC_ERR = -11,
    READ_ERR,
    WRONG_DATA
};

typedef struct node node_t;

struct node
{
    char data[PART_LEN];
    node_t *next;
};

int read_line(FILE *f, char **s, size_t *s_len);
void delete_dup_spaces(node_t **head);
int concat(node_t **dst, node_t *head1, node_t *head2);
int find_substr(size_t *index, node_t *str, node_t *substr);

void print_list(node_t *head);
int alloc_node(node_t **node);
int create_list(node_t **head);
int init_list(node_t **head, char *s);
void free_list(node_t **head);

#endif