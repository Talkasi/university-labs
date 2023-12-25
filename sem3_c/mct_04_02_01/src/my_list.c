#include "my_list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int create_list_from_keyboard(node_t **head)
{
    *head = NULL;
    int tmp;
    node_t *cur_node = NULL;
    while (scanf("%d", &tmp) == 1)
    {
        node_t *new_node = calloc(1, sizeof(node_t));
        if (new_node == NULL)
        {
            free_list(head);
            return ALLOC_ERR;
        }

        new_node->data = tmp;
        if (cur_node)
        {
            cur_node->next = new_node;
            cur_node = cur_node->next;
        }
        else
        {
            *head = new_node;
            cur_node = *head;
        }
    }

    return 0;
}

void free_list(node_t **head)
{
    if (head == NULL || *head == NULL)
        return;

    for (node_t *cur_node = *head; cur_node;)
    {
        node_t *tmp = cur_node->next;
        free(cur_node);
        cur_node = tmp;
    }

    *head = NULL;
}

int swap_second_with_max(node_t **head)
{
    if (head == NULL)
        return WRONG_LIST_ERR;

    if (*head == NULL || (*head)->next == NULL)
        return 0;

    node_t *max = *head;
    for (node_t *cur_node = (*head)->next; cur_node; cur_node = cur_node->next)
        if (cur_node->data > max->data)
            max = cur_node;

    int tmp = max->data;
    max->data = (*head)->next->data;
    (*head)->next->data = tmp;

    return 0;
}

int delete_third_min(node_t **head)
{
    if (head == NULL || *head == NULL)
        return WRONG_LIST_ERR;

    int n_mins = 3;
    node_t *mins[] = {*head, NULL, NULL};
    node_t *parents[] = {NULL, NULL, NULL};

    node_t *cur_parent = *head;
    for (node_t *cur_node = (*head)->next; cur_node; cur_node = cur_node->next)
    {
        for (int i = 0; i < n_mins; ++i)
        {
            if (mins[i] == NULL)
            {
                mins[i] = cur_node;
                parents[i] = cur_parent;
                break;
            }
            else if (cur_node->data < mins[i]->data)
            {
                memmove(&mins[i + 1], &mins[i], (n_mins - i - 1) * sizeof(node_t *));
                memmove(&parents[i + 1], &parents[i], (n_mins - i - 1) * sizeof(node_t *));
                mins[i] = cur_node;
                parents[i] = cur_parent;
                break;
            }
        }

        cur_parent = cur_node;
    }

    if (mins[2] != NULL)
    {
        if (parents[2] != NULL)
            parents[2]->next = mins[2]->next;
        else
            (*head) = mins[2]->next;

        free(mins[2]);
    }

    return 0;
}

void print_list(node_t *head)
{
    for (node_t *cur_node = head; cur_node; cur_node = cur_node->next)
        printf("%d ", cur_node->data);

    printf("\n");
}
