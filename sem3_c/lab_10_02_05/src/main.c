#include "list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define COMMAND_LEN 3

typedef enum
{
    INVALID,
    OUT,
    CAT,
    SPS,
    POS
} command_t;

enum err
{
    INVALID_COMMAND = -100
};

command_t get_command();

int main()
{
    int rc;
    command_t c = get_command();
    if (c == INVALID)
        return INVALID_COMMAND;

    if (c == OUT)
    {
        node_t *head;
        if ((rc = create_list(&head)))
            return rc;

        print_list(head);
        free_list(&head);
    }

    if (c == CAT)
    {
        node_t *head1;
        node_t *head2;
        if ((rc = create_list(&head1)))
            return rc;

        if ((rc = create_list(&head2)))
        {
            free_list(&head1);
            return rc;
        }

        node_t *result;
        if ((rc = concat(&result, head1, head2)))
        {
            free_list(&head1);
            free_list(&head2);
            return rc;
        }

        print_list(result);
        free_list(&result);
        free_list(&head1);
        free_list(&head2);
    }

    if (c == SPS)
    {
        node_t *head;
        if ((rc = create_list(&head)))
            return rc;

        delete_dup_spaces(&head);
        print_list(head);
        free_list(&head);
    }

    if (c == POS)
    {
        node_t *head1;
        node_t *head2;
        if ((rc = create_list(&head1)))
            return rc;

        if ((rc = create_list(&head2)))
        {
            free_list(&head1);
            return rc;
        }

        size_t index;
        if (find_substr(&index, head1, head2) == 0)
            printf("%zu\n", index);
        else
            printf("-1\n");

        free_list(&head1);
        free_list(&head2);
    }

    return 0;
}

command_t get_command()
{
    char *command;
    command_t rc = INVALID;
    size_t len;

    if (!read_line(stdin, &command, &len))
    {
        if (strcmp(command, "out") == 0)
            rc = OUT;
        if (strcmp(command, "cat") == 0)
            rc = CAT;
        if (strcmp(command, "sps") == 0)
            rc = SPS;
        if (strcmp(command, "pos") == 0)
            rc = POS;
        free(command);
    }

    return rc;
}
