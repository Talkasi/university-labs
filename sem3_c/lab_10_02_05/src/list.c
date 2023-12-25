#define _GNU_SOURCE
#include "list.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void free_str(char *s, size_t *s_len)
{
    free(s);
    s = NULL;
    *s_len = 0;
}

void del_new_line(char *s, size_t *s_len)
{
    if (s[*s_len - 1] == '\n')
        s[--*s_len] = '\0';
}

int all_space(char *s, size_t s_len)
{
    for (size_t i = 0; i < s_len; ++i)
        if (!isspace(s[i]))
            return 0;

    return 1;
}

int read_line(FILE *f, char **s, size_t *s_len)
{
    *s = NULL;
    ssize_t tmp_s_len;
    if ((tmp_s_len = getline(s, s_len, f)) == -1)
    {
        free_str(*s, s_len);
        return READ_ERR;
    }

    *s_len = tmp_s_len;

    del_new_line(*s, s_len);
    if (all_space(*s, *s_len) || *s_len == 0)
    {
        free_str(*s, s_len);
        return READ_ERR;
    }

    return 0;
}

int alloc_node(node_t **node)
{
    void *tmp = calloc(1, sizeof(node_t));
    if (tmp == NULL)
        return ALLOC_ERR;

    *node = tmp;
    return 0;
}

int create_list(node_t **head)
{
    int rc;
    char *tmp_s;
    size_t tmp_s_len;

    if ((rc = read_line(stdin, &tmp_s, &tmp_s_len)))
        return rc;

    if ((rc = init_list(head, tmp_s)))
    {
        free(tmp_s);
        return rc;
    }

    free(tmp_s);
    return 0;
}

int init_list(node_t **head, char *s)
{
    int rc;
    node_t *cur_node;
    if ((rc = alloc_node(&cur_node)))
        return rc;

    *head = cur_node;
    size_t i;
    for (i = 0; s[i] != '\0'; ++i)
    {
        cur_node->data[i % PART_LEN] = s[i];
        if (i % PART_LEN == PART_LEN - 1)
        {
            if ((rc = alloc_node(&cur_node->next)))
            {
                free_list(head);
                return rc;
            }

            cur_node = cur_node->next;
        }
    }

    cur_node->data[i % PART_LEN] = '\0';
    return 0;
}

void print_list(node_t *head)
{
    for (node_t *cur_node = head; cur_node; cur_node = cur_node->next)
        printf("%.*s", PART_LEN, cur_node->data);

    printf("\n");
}

void free_list(node_t **head)
{
    for (node_t *cur_node = *head; cur_node;)
    {
        node_t *tmp = cur_node->next;
        free(cur_node);
        cur_node = tmp;
    }

    *head = NULL;
}

int copy_list(node_t **dst, node_t *src, node_t **last_dst_node)
{
    int rc;
    if (src == NULL)
    {
        *dst = NULL;
        return 0;
    }

    if ((rc = alloc_node(dst)))
        return rc;

    node_t *cur_result_node = *dst;
    node_t *cur_node = src;
    for (; cur_node->next; cur_node = cur_node->next)
    {
        memcpy(cur_result_node->data, cur_node->data, PART_LEN * sizeof(char));
        if ((rc = alloc_node(&cur_result_node->next)))
        {
            free_list(dst);
            return rc;
        }
        cur_result_node = cur_result_node->next;
    }

    memcpy(cur_result_node->data, cur_node->data, PART_LEN * sizeof(char));
    cur_result_node->next = NULL;
    *last_dst_node = cur_result_node;

    return 0;
}

int is_empty_piece(node_t *node)
{
    size_t n_empty = 0;
    for (size_t i = 0; i < PART_LEN; ++i)
        if (node->data[i] == '\0')
            ++n_empty;

    if (n_empty == PART_LEN)
        return 1;

    return 0;
}

int is_finished_piece(node_t *node)
{
    for (size_t i = 0; i < PART_LEN; ++i)
        if (node->data[i] == '\0')
            return 1;

    return 0;
}

int concat(node_t **dst, node_t *head1, node_t *head2)
{
    int rc;
    *dst = NULL;
    node_t *last_dst_node;

    if (head1 == NULL)
        return copy_list(dst, head2, &last_dst_node);

    if (head2 == NULL)
        return copy_list(dst, head1, &last_dst_node);

    if ((rc = copy_list(dst, head1, &last_dst_node)))
        return rc;

    size_t save = strlen(last_dst_node->data);
    size_t shift = PART_LEN - save;

    node_t *parent = NULL;
    node_t *cur_dst_node = last_dst_node;
    for (node_t *cur_node = head2; cur_node; cur_node = cur_node->next)
    {
        memcpy(&cur_dst_node->data[save], cur_node->data, shift * sizeof(char));

        if ((rc = alloc_node(&cur_dst_node->next)))
        {
            free_list(dst);
            return rc;
        }

        parent = cur_dst_node;
        cur_dst_node = cur_dst_node->next;
        memmove(cur_dst_node->data, &cur_node->data[shift], save * sizeof(char));
    }

    if (parent && is_empty_piece(cur_dst_node) && is_finished_piece(parent))
    {
        parent->next = NULL;
        free(cur_dst_node);
    }

    return 0;
}

void delete_dup_spaces(node_t **head)
{
    if (*head == NULL)
        return;

    node_t *cur_node = *head;
    node_t *next_valid_node = cur_node;
    size_t cur_i = 0;
    size_t next_valid_i = 1;

    while (next_valid_node->data[next_valid_i] != '\0')
    {
        if (!(cur_node->data[cur_i] == next_valid_node->data[next_valid_i] && isspace(cur_node->data[cur_i])))
        {
            cur_i = (cur_i + 1) % PART_LEN;
            if (cur_i == 0)
                cur_node = cur_node->next;
            cur_node->data[cur_i] = next_valid_node->data[next_valid_i++];
        }
        else
            next_valid_i++;

        next_valid_i %= PART_LEN;

        if (next_valid_i == 0)
            next_valid_node = next_valid_node->next;
    }

    cur_i = (cur_i + 1) % PART_LEN;
    if (cur_i == 0)
        cur_node = cur_node->next;

    cur_node->data[cur_i] = '\0';
    free_list(&cur_node->next);
    cur_node->next = NULL;
}

int str_start_equal(node_t *str, size_t str_i, node_t *start_str)
{
    size_t start_str_i = 0;

    while (start_str->data[start_str_i] != '\0' && str->data[str_i] != '\0')
    {
        if (start_str->data[start_str_i] != str->data[str_i])
            return 0;

        start_str_i = (start_str_i + 1) % PART_LEN;
        str_i = (str_i + 1) % PART_LEN;

        if (start_str_i == 0)
            start_str = start_str->next;
        if (str_i == 0)
            str = str->next;
    }

    if (start_str->data[start_str_i] != '\0')
        return 0;

    return 1;
}

int find_substr(size_t *index, node_t *str, node_t *substr)
{
    if (str == NULL || substr == NULL)
        return NOT_FOUND;

    *index = 0;
    node_t *cur_node = str;
    size_t cur_i = 0;
    while (cur_node->data[cur_i] != '\0')
    {
        if (str_start_equal(cur_node, cur_i, substr))
            return 0;

        cur_i = (cur_i + 1) % PART_LEN;
        if (cur_i == 0)
            cur_node = cur_node->next;

        ++*index;
    }

    return NOT_FOUND;
}
