#ifndef MY_LIST_H
#define MY_LIST_H

enum err
{
    ALLOC_ERR,
    WRONG_LIST_ERR
};

typedef struct node node_t;

struct node
{
    int data;
    node_t *next;
};

int create_list_from_keyboard(node_t **head);
void free_list(node_t **head);
int swap_second_with_max(node_t **head);
int delete_third_min(node_t **head);
void print_list(node_t *head);

#endif