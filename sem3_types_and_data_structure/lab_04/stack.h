#ifndef STACK_H
#define STACK_H
#include <stdio.h>

#define STACK_FULL -100
#define STACK_EMPTY -101
#define STACK_OWERFLOW_ERR -102
#define MALLOC_ERR -103

#define STACK_SIZE 10000
#define LOG_SIZE 1000
#define MAX_GEN_N 1000

struct arr_stack {
	int data[STACK_SIZE];
	ssize_t ps;
};

typedef struct arr_stack arr_stack_t;
typedef struct node node_t;
typedef struct list_stack list_stack_t;

struct node {
	int el;
	node_t *next;
};

struct list_stack {
	node_t *head;

	node_t *free_log[LOG_SIZE];
	size_t n_freed;
	size_t n_els;
};

int push_as(arr_stack_t *s, int new_el);
int pop_as(arr_stack_t *s, int *el);
int print_as(arr_stack_t *s);

int sort_as(arr_stack_t *s);
int merge_sorted_as(arr_stack_t *s1, arr_stack_t *s2, arr_stack_t *res_s);

int pre_init_ls(list_stack_t *s);
void free_ls(list_stack_t *s);

int push_ls(list_stack_t *s, int new_el);
int pop_ls(list_stack_t *s, int *el);
int print_ls(list_stack_t *s);
void print_freed_log(list_stack_t *s);

int sort_ls(list_stack_t *s);
int merge_sorted_ls(list_stack_t *s1, list_stack_t *s2, list_stack_t *res_s);

void g_rand_as(arr_stack_t *s, size_t n_els);
void g_rand_ls(list_stack_t *s, size_t n_els);

void cp_ls(node_t *src, list_stack_t *dst);

#endif