#include <stdlib.h>

typedef struct block block_t;

struct block
{
    int free;
    size_t n;
    block_t *next;
};

// VERY IMPORTANT THING
#define HEAP_SIZE 2000
static char my_heap[HEAP_SIZE];

static block_t *head = (block_t *)my_heap;

static void initialize(void)
{
    head->size = sizeof(my_heap) - sizeof(block_t);
    head->free = 1;
    head->next = NULL;
}

void split_blocks(block_t *b, size_t n)
{
    if (n + sizeof(block_t) >= b->size)
    {
        block_t *new_block = (block_t *)((char *)b + n + sizeof(block_t));
        new_block->free = 1;
        new_block->size = b->size - n - sizeof(block_t);
        b->size = n;
        b->next = new_block;
    }
}

void *my_malloc(size_t n)
{
    assert(n != 0 && n < HEAP_SIZE);

    block_t *cur = head;
    for (; cur; cur = cur->next)
    {
        if (cur->size >= n)
        {
            split_blocks(cur, n);
            cur->free = 0;
            return ++cur;
        }
    }

    return NULL;
}

void merge_blocks()
{
    block_t *cur = head;
    while (cur && cur->next)
    {
        if (cur->next->free && cur->free)
        {
            cur->size += cur->next->size + sizeof(block_t);
            cur->next = cur->next->next;
        }
        else
            cur = cur->next;
    }
}

void my_free(void *p)
{
    block_t *b = p;
    --b;
    b->free = 1;
    merge_blocks();
}
