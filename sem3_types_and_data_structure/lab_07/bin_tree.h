#ifndef BIN_TREE_H
#define BIN_TREE_H
#include <stdio.h>

#define MAX_STR_LEN 256
#define MAX_WORD_LEN 40

typedef enum {
	ALLOC_ERR = -10,
	BAD_IMAGE = -11,
	FILE_ERR
} errs;

typedef struct node node_t;

struct node {
	char data[MAX_WORD_LEN];

	node_t *left;
	node_t *right;

	int height;
};

size_t fread_line(FILE *f, char *s, size_t max_len);
int alloc_node(node_t **node);
void free_tree(node_t **node);
int create_node(node_t **node, char *s);
void tree_apply(void *f, node_t *root, void (*func)(void *, node_t *));
int open_tree_img(char *file_name, node_t *root);
node_t *put_data(node_t *root, node_t *new_node);
int create_tree_from_file(FILE *f, node_t **root);
void copyFile(const char* sourceFileName, const char* destinationFileName);

int delete_by_first_letter_file(char *fileName, char c);
node_t *delete_by_first_letter_tree(node_t *root, char c);
node_t *delete_data(node_t *root, char *key);

void printInorder(node_t *node);
void printPreorder(node_t *node);
void printPostorder(node_t *node);

int get_balance(node_t *node);
node_t *right_rotate(node_t *root);
node_t *left_rotate(node_t *root);
node_t *insert_balanced(node_t *node, char *data);
void preorderApply(node_t **balanced_tree, node_t *search_tree, node_t *func(node_t *, char *));
int create_balanced_from_bin_search_tree(node_t **balanced_tree, node_t *search_tree);

node_t *search_bin_tree(node_t *root, char *key, size_t *n_compares);
void calc_node_size(node_t *tree, size_t *size);
void calc_size_apply(node_t *search_tree, void func(node_t *, size_t *), size_t *size);


#endif