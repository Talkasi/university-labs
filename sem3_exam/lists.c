#include <stdlib.h>

typedef struct node node_t;

struct node
{
    int data;
    node_t *next;
};

node_t *create_node(int *data)
{
    node_t *new = calloc(1, sizeof(node_t));
    if (new)
        new->data = data;
    return new;
}

void *free_list(node_t *head)
{
    node_t *tmp;
    for (node_t *cur = head; cur; cur = tmp)
    {
        tmp = cur->next;
        free(cur);
    }
}

node_t *insert_front(node_t *head, node_t *new)
{
    new->next = head;
    return new;
}

node_t *insert_back(node_t *head, node_t *new)
{
    if (!head)
        return new;

    node_t *cur = head;
    for (; cur->next; cur = cur->next)
        ;

    cur->next = new;
    return head;
}

node_t *insert_before(node_t *head, node_t *new, node_t *before)
{
    node_t *cur = head;
    node_t *prev = NULL;
    for (; cur; cur = cur->next)
    {
        if (cur->data == before->data)
        {
            new->next = cur;
            prev->next = new;
            return head;
        }
        prev = cur;
    }
    return NULL;
}

node_t *insert_after(node_t *head, node_t *new, node_t *after)
{
    node_t *cur = head;

    for (; cur; cur = cur->next)
    {
        if (cur->data == after->data)
        {
            new->next = cur->next;
            cur->next = new;
            return head;
        }
    }

    return NULL;
}

void apply(node_t *head, int (*f)(void *node, void *param), void *param)
{
    node_t *cur = head;
    for (; cur; cur = cur->next)
        f(cur, param);
}

node_t *remove(node_t *head, int data)
{
    node_t *cur = head;
    node_t *prev = NULL;
    for (; cur; cur = cur->next)
    {
        if (cur->data == data)
            break;
        prev = cur;
    }

    if (!cur)
        return NULL;

    if (prev)
    {
        prev->next = cur->next;
        free(cur);
        return head;
    }

    head = head->next;
    free(cur);
    return head;
}
