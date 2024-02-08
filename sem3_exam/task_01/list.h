#ifndef LIST_H
#define LIST_H

typedef struct my_node node_t;

struct my_node
{
    int first;
    int second;
    int third;
    node_t *next;
};

void free_list(node_t **head);
void insert_end_list(node_t **head, node_t *new_node);
int read_to_node(node_t **node);

#endif
