#include "bin_tree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

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

void free_tree(node_t **node) {
    if (*node != NULL) {
        free_tree(&(*node)->right);
        free_tree(&(*node)->left);
        free(*node);
        *node = NULL;
    }
}

int create_node(node_t **node, char *s) {
	int rc;
	if ((rc = alloc_node(node)))
		return rc;

	strcpy((*node)->data, s);
	return 0;
}

void tree_apply(void *f, node_t *root, void (*func)(void *, node_t *))
{
    if (!root)
        return;

    func(f, root);
    tree_apply(f, root->left, func);
    tree_apply(f, root->right, func);
}

void node_to_dot(void *file, node_t *root)
{
    FILE *f = file;

    if (root->left)
        fprintf(f, "%s -> %s;\n", root->data, root->left->data);

    if (root->right)
        fprintf(f, "%s -> %s;\n", root->data, root->right->data);
}

void tree_to_dot(FILE *f, char *bin_tree_name, node_t *root)
{
    fprintf(f, "digraph %s {\n\
    node [shape=oval, fontname=\"Arial\", fontsize=12];\
    edge [fontsize=10];",
    bin_tree_name);

    tree_apply(f, root, node_to_dot);

    fprintf(f, "}\n");
}

int open_tree_img(char *file_name, node_t *root)
{
    char path[MAX_STR_LEN];
    sprintf(path, "./img/%s.dot", file_name);

    FILE *out_img = fopen(path, "w");
    if (!out_img)
        return BAD_IMAGE;

    tree_to_dot(out_img, "binary_search_tree", root);
    fclose(out_img);

    char command[MAX_STR_LEN * 2];
    sprintf(command, "dot -Tpng %s -o ./img/%s.png && sxiv ./img/%s.png &", path, file_name, file_name);
    system(command);
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
    fseek(f, 0, SEEK_SET);

	node_t *new_node;
	size_t i = 0;
    char word[MAX_STR_LEN];
	while (fread_line(f, word, MAX_WORD_LEN)) {
		if ((rc = create_node(&new_node, word)))
			return rc;
		*root = put_data(*root, new_node);
		++i;
	}

	return 0;
}

void copyFile(const char *sourceFileName, const char *destinationFileName) {
    FILE *sourceFile, *destinationFile;
    char ch;

    sourceFile = fopen(sourceFileName, "r");
    if (sourceFile == NULL) {
        printf("Error opening the source file\n");
        return;
    }

    destinationFile = fopen(destinationFileName, "w");
    if (destinationFile == NULL) {
        printf("Error creating the destination file\n");
        return;
    }

    while ((ch = fgetc(sourceFile)) != EOF) {
        fputc(ch, destinationFile);
    }

    fclose(sourceFile);
    fclose(destinationFile);
}

int delete_by_first_letter_file(char *fileName, char c) {
	char word[100];

    FILE *file = fopen(fileName, "r+");
    if (file == NULL)
        return FILE_ERR;

    long wp = 0;
    while (fscanf(file, "%s", word) != EOF) {
        if (word[0] != c) {
            long cp = ftell(file);
            fseek(file, wp, SEEK_SET);
            fprintf(file, "%s\n", word);
            wp = ftell(file);
            fseek(file, cp, SEEK_SET);
        }
    }

    ftruncate(fileno(file), wp);
    return 0;
}

void printInorder(node_t *node)
{
    if (node == NULL)
        return;
 
    printInorder(node->left);
    printf("%s ", node->data);
    printInorder(node->right);
}

void printPreorder(node_t *node)
{
    if (node == NULL)
        return;

    printf("%s ", node->data);
    printPreorder(node->left);
    printPreorder(node->right);
}

void printPostorder(node_t *node)
{
    if (node == NULL)
        return;
 
    printPostorder(node->left);
    printPostorder(node->right);
    printf("%s ", node->data);
}

node_t *delete_by_first_letter_tree(node_t *root, char c)
{
    if (root == NULL)
        return root;
 
    if (root->data[0] != c) {
        root->left = delete_by_first_letter_tree(root->left, c);
        root->right = delete_by_first_letter_tree(root->right, c);
        return root;
    }
 
    if (root->left == NULL) {
        node_t *tmp = root->right;
        free(root);
        return delete_by_first_letter_tree(tmp, c);
    } else if (root->right == NULL) {
        node_t *tmp = root->left;
        free(root);
        return delete_by_first_letter_tree(tmp, c);
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
 
        strcpy(root->data, successor->data);
        free(successor);

        return delete_by_first_letter_tree(root, c);
    }
}

node_t *delete_data(node_t *root, char *key)
{
    if (root == NULL)
        return root;
 
    if (strcmp(root->data, key) > 0) {
        root->left = delete_data(root->left, key);
        return root;
    } else if (strcmp(root->data, key) < 0) {
        root->right = delete_data(root->right, key);
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
 
        strcpy(root->data, successor->data);
        free(successor);
        return root;
    }
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

int height(node_t *node) {
    if (node == NULL)
        return 0;

    return node->height;
}

int get_balance(node_t *node) {
    if (node == NULL)
        return 0;

    return height(node->left) - height(node->right);
}

node_t *right_rotate(node_t *root) {
    node_t *new_root = root->left;
    node_t *prev_right_tail = new_root->right;

    new_root->right = root;
    root->left = prev_right_tail;

    root->height = max(height(root->left), height(root->right)) + 1;
    new_root->height = max(height(new_root->left), height(new_root->right)) + 1;

    return new_root;
}

node_t *search_bin_tree(node_t *root, char *key, size_t *n_compares) {
    if (root == NULL)
        return root;
    
    ++*n_compares;
    if (strcmp(root->data, key) == 0)
        return root;
    
    ++*n_compares;
    if (strcmp(root->data, key) > 0)
        return search_bin_tree(root->left, key, n_compares);
    else
        return search_bin_tree(root->right, key, n_compares);
}


node_t *left_rotate(node_t *root) {
    node_t *new_root = root->right;
    node_t *prev_left_tail = new_root->left;

    new_root->left = root;
    root->right = prev_left_tail;

    root->height = max(height(root->left), height(root->right)) + 1;
    new_root->height = max(height(new_root->left), height(new_root->right)) + 1;

    return new_root;
}

node_t *insert_balanced(node_t *node, char *data) {
    if (node == NULL) {
        node_t *new_node = calloc(1, sizeof(node_t));
        if (new_node == NULL)
            return NULL;

        memcpy(new_node->data, data, MAX_WORD_LEN);
        new_node->height = 1;
        return new_node;
    }

    if (strcmp(data, node->data) < 0)
        node->left = insert_balanced(node->left, data);
    else if (strcmp(data, node->data) > 0)
        node->right = insert_balanced(node->right, data);
    else
        return node;

    node->height = max(height(node->left), height(node->right)) + 1;

    int balance = get_balance(node);
    if (balance > 1 && strcmp(data, node->left->data) < 0)
        return right_rotate(node);

    if (balance < -1 && strcmp(data, node->right->data) > 0)
        return left_rotate(node);

    if (balance > 1 && strcmp(data, node->left->data) > 0) {
        node->left = left_rotate(node->left);
        return right_rotate(node);
    }

    if (balance < -1 && strcmp(data, node->right->data) < 0) {
        node->right = right_rotate(node->right);
        return left_rotate(node);
    }

    return node;
}

void preorderApply(node_t **balanced_tree, node_t *search_tree, node_t *func(node_t *, char *)) {
    if (search_tree == NULL)
        return;

    node_t *tmp = func(*balanced_tree, search_tree->data);
    if (tmp == NULL) {
        free_tree(balanced_tree);
        return;
    }
    *balanced_tree = tmp;

    preorderApply(balanced_tree, search_tree->left, func);
    preorderApply(balanced_tree, search_tree->right, func);
}

void calc_node_size(node_t *tree, size_t *size) {
    *size += sizeof(tree);
}

void calc_size_apply(node_t *search_tree, void func(node_t *, size_t *), size_t *size) {
    if (search_tree == NULL)
        return;

    func(search_tree, size);
    calc_size_apply(search_tree->left, func, size);
    calc_size_apply(search_tree->right, func, size);
}

int create_balanced_from_bin_search_tree(node_t **balanced_tree, node_t *search_tree) {
    preorderApply(balanced_tree, search_tree, insert_balanced);
    if (*balanced_tree == NULL && search_tree != NULL)
        return ALLOC_ERR;

    return 0;
}
