#ifndef BIN_TREE_H
#define BIN_TREE_H
#include <stdio.h>

#define MAX_STR_LEN 256

typedef enum {
	ALLOC_ERR = -10
} errs;

typedef struct node node_t;

struct node {
	char *data;

	node_t *left;
	node_t *right;
};

int alloc_node(node_t **node);
int create_node(node_t **node, char *s);

node_t *put_data(node_t *root, node_t *new_node);
int create_tree_from_file(FILE *f, node_t **root);
node_t *delete_by_first_letter(node_t *root, char c);

#endif