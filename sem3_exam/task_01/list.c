#include "list.h"
#include <stdio.h>

void free_list(node_t **head)
{
    node_t *tmp;
    for (node_t *cur_node = *head; cur_node; cur_node = tmp)
    {
        tmp = cur_node->next;
        free(cur_node);
    }
}

void insert_end_list(node_t **head, node_t *new_node)
{
    if (*head == NULL)
    {
        new_node->next = NULL;
        *head = new_node;
        return;
    }

    node_t *cur_node = *head;
    for (; cur_node->next; cur_node = cur_node->next)
        ;

    cur_node->next = new_node;
}

int read_to_node(node_t **node)
{
    *node = calloc(1, sizeof(node_t));
    if (!*node)
        return ALLOC_ERR;

    if (scanf("%d%d%d", &(*node->first), &(*node)->second, &(*node)->third) != 3)
    {
        free(*node);
        return READ_ERR;
    }

    return 0;
}
