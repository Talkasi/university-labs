#include "my_list.h"
#include "stdio.h"

int main()
{
    int rc;
    node_t *head = NULL;

    if ((rc = create_list_from_keyboard(&head)))
        return rc;

    if ((rc = delete_third_min(&head)))
    {
        free_list(&head);
        return rc;
    }

    if ((rc = swap_second_with_max(&head)))
    {
        free_list(&head);
        return rc;
    }

    print_list(head);
    free_list(&head);

    return 0;
}
