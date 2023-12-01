#include "bin_tree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

size_t fread_line(FILE *f, char *s, size_t max_len)
{
    char tmp[MAX_STR_LEN];
    if (max_len > MAX_STR_LEN)
        return 0;

    if (fgets(tmp, MAX_STR_LEN, f) == NULL)
        return 0;

    size_t len_tmp = strlen(tmp);
    if (tmp[len_tmp - 1] != '\n')
        return 0;

    tmp[--len_tmp] = '\0';
    if (len_tmp >= max_len)
        return 0;

    strcpy(s, tmp);
    return len_tmp;
}

int alloc_node(node_t **node) {
	*node = calloc(1, sizeof(node_t));
	if (!*node)
		return ALLOC_ERR;

	return 0;
}

int create_node(node_t **node, char *s) {
	int rc;
	if ((rc = alloc_node(node)))
		return rc;

	(*node)->data = s;
	return 0;
}

node_t *put_data(node_t *root, node_t *new_node) {
    if (root == NULL)
        return new_node;
 
    if (strcmp(new_node->data, root->data) < 0)
        root->left = put_data(root->left, new_node);
    else if (strcmp(new_node->data, root->data) > 0)
        root->right = put_data(root->right, new_node);
 
    return root;
}

int create_tree_from_file(FILE *f, node_t **root) {
	int rc;
	char word[MAX_STR_LEN];

	node_t *new_node;
	while (fread_line(f, word, MAX_STR_LEN)) {
		if ((rc = create_node(&new_node, word)))
			return rc;
		*root = put_data(*root, new_node);
	}

	return 0;
}

node_t *delete_by_first_letter(node_t *root, char c)
{
    if (root == NULL)
        return root;
 
    if (root->data[0] > c) {
        root->left = delete_by_first_letter(root->left, c);
        return root;
    } else if (root->data[0] < c) {
        root->right = delete_by_first_letter(root->right, c);
        return root;
    }
 
    if (root->left == NULL) {
        node_t *tmp = root->right;
        free(root);
        return tmp;
    } else if (root->right == NULL) {
        node_t *tmp = root->left;
        free(root);
        return tmp;
    } else {
        node_t *successor_parent = root;
        node_t *successor = root->right;
        while (successor->left != NULL) {
            successor_parent = successor;
            successor = successor->left;
        }

        if (successor_parent != root)
            successor_parent->left = successor->right;
        else
            successor_parent->right = successor->right;
 
        root->data = successor->data;
        free(successor);
        return root;
    }
}
