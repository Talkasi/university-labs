#include "stack.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

enum c {
	NOTHING,
	TMP1,
	TMP2,
	BOTH
};

int	pre_init_ls(list_stack_t *s)
{
	s->head = malloc(sizeof(node_t));
	if (!s->head)
		return MALLOC_ERR;

	memset(s->head, 0, sizeof(node_t));
	s->n_freed = 0;
	s->n_els = 0;
	return 0;
}


void	free_ls(list_stack_t *s)
{
	node_t * free_helper;
	for (node_t * tmp_node = s->head; tmp_node; tmp_node = free_helper) {
		free_helper = tmp_node->next;
		free(tmp_node);
	}
}

int	push_ls(list_stack_t *s, int new_el)
{
	if (s->n_els + 1 > STACK_SIZE)
		return STACK_FULL;

	node_t * new_node;
	new_node = (node_t * ) malloc(sizeof(node_t));
	if (!new_node)
		return MALLOC_ERR;

	new_node->el = new_el;
	new_node->next = s->head;
	s->head = new_node;
	++s->n_els;

	return 0;
}


int	pop_ls(list_stack_t *s, int *el)
{
	node_t * next_node = NULL;

	if (!s->head->next)
		return STACK_EMPTY;

	next_node = s->head->next;
	*el = s->head->el;

	if (s->n_freed >= LOG_SIZE)
		s->n_freed = 0;
		//printf("Warning! Free log is full.\n");
	else
		s->free_log[s->n_freed++] = s->head;
	free(s->head);

	s->head = next_node;
	--s->n_els;

	return 0;
}


int	print_ls(list_stack_t *s)
{
	if (!s->head->next) {
		printf("Stack is empty.\n");
		return STACK_EMPTY;
	}

	printf("┌────────────────────┬────────────────────┐\n"
	    "│      Address       │       Element      │\n"
	    "├────────────────────┼────────────────────┤\n");

	for (node_t * tmp_node = s->head; tmp_node->next; tmp_node = tmp_node->next)
		printf("│ %18p │ %18d │\n", tmp_node, tmp_node->el);

	printf("└────────────────────┴────────────────────┘\n");
	return 0;
}


void 	print_freed_log(list_stack_t *s)
{
	if (s->n_freed == 0) {
		printf("Nothing was freed yet.\n");
		return;
	}

	printf("┌────────────────────┬────────────────────┐\n"
	    "│  Number of a free  │    Address freed   │\n"
	    "├────────────────────┼────────────────────┤\n");

	for (size_t i = 0; i < s->n_freed; ++i)
		printf("│ %18zu │ %18p │\n", i, s->free_log[i]);

	printf("└────────────────────┴────────────────────┘\n");
}

void cp_ls(node_t *list, list_stack_t *p)
{
	node_t *tmp = list;
	while (tmp) {
		push_ls(p, list->el);
		tmp = tmp->next;
	}
}

int	sort_ls(list_stack_t *s)
{
	if (s->n_els > STACK_SIZE)
		return STACK_OWERFLOW_ERR;

	list_stack_t tmp;
	if (pre_init_ls(&tmp))
		return MALLOC_ERR;

	int	tmp_el;
	int	tmp_top;

	while (s->head->next != NULL) {
		pop_ls(s, &tmp_el);

		while (tmp.head->next != NULL && tmp_top > tmp_el) {
			pop_ls(&tmp, &tmp_top);
			push_ls(s, tmp_top);
		}

		push_ls(&tmp, tmp_el);
		tmp_top = tmp_el;
	}

	while (tmp.head->next != NULL) {
		pop_ls(&tmp, &tmp_el);
		push_ls(s, tmp_el);
	}

	free_ls(&tmp);

	return 0;
}


int	merge_sorted_ls(list_stack_t *s1, list_stack_t *s2, list_stack_t *res_s)
{
	if (s1->n_els + s2->n_els > STACK_SIZE)
		return STACK_OWERFLOW_ERR;

	int	tmp_s1;
	int	tmp_s2;
	int	cur_stage = BOTH;

	while (s1->head->next != NULL && s2->head->next != NULL) {
		if (cur_stage == TMP1 || cur_stage == BOTH)
			pop_ls(s1, &tmp_s1);

		if (cur_stage == TMP2 || cur_stage == BOTH)
			pop_ls(s2, &tmp_s2);

		if (tmp_s1 < tmp_s2) {
			push_ls(res_s, tmp_s1);
			cur_stage = TMP1;
		} else {
			push_ls(res_s, tmp_s2);
			cur_stage = TMP2;
		}
	}

	if (cur_stage == TMP2)
		push_ls(res_s, tmp_s1);

	if (cur_stage == TMP1)
		push_ls(res_s, tmp_s2);

	while (s1->head->next != NULL) {
		pop_ls(s1, &tmp_s1);
		push_ls(res_s, tmp_s1);
	}

	while (s2->head->next != NULL) {
		pop_ls(s2, &tmp_s2);
		push_ls(res_s, tmp_s2);
	}

	return 0;
}


int	push_as(arr_stack_t *s, int new_el)
{
	if (s->ps + 1 >= STACK_SIZE)
		return STACK_FULL;

	s->ps += 1;
	s->data[s->ps] = new_el;

	return 0;
}


int	pop_as(arr_stack_t *s, int *el)
{
	if (s->ps == -1)
		return STACK_EMPTY;

	*el = s->data[s->ps];
	--s->ps;
	return 0;
}


int	print_as(arr_stack_t *s)
{
	if (s->ps == -1) {
		printf("Stack is empty.\n");
		return STACK_EMPTY;
	}

	printf("┌────────────────────┬────────────────────┐\n"
	    "│  Number of element │       Element      │\n"
	    "├────────────────────┼────────────────────┤\n");
	for (size_t i = 0; i < s->ps + 1; ++i)
		printf("│ %18zu │ %18d │\n", i, s->data[i]);
	printf("└────────────────────┴────────────────────┘\n");
	return 0;
}


int	sort_as(arr_stack_t *s)
{
	if (s->ps >= STACK_SIZE)
		return STACK_OWERFLOW_ERR;

	if (s->ps == -1)
		return STACK_EMPTY;

	arr_stack_t tmp;
	tmp.ps = -1;

	int	tmp_el;
	int	tmp_top;

	while (s->ps != -1) {
		pop_as(s, &tmp_el);

		while (tmp.ps != -1 && tmp_top > tmp_el) {
			pop_as(&tmp, &tmp_top);
			push_as(s, tmp_top);
		}

		push_as(&tmp, tmp_el);
		tmp_top = tmp_el;
	}

	while (tmp.ps != -1) {
		pop_as(&tmp, &tmp_el);
		push_as(s, tmp_el);
	}

	return 0;
}


int	merge_sorted_as(arr_stack_t *s1, arr_stack_t *s2, arr_stack_t *res_s)
{
	//printf("%zi %zi %d\n", s1->ps, s2->ps, STACK_SIZE);
	if (s1->ps + s2->ps + 2 > STACK_SIZE)
		return STACK_OWERFLOW_ERR;

	int	tmp_s1;
	int	tmp_s2;
	int	cur_stage = BOTH;

	while (s1->ps != -1 && s2->ps != -1) {
		if (cur_stage == TMP1 || cur_stage == BOTH)
			pop_as(s1, &tmp_s1);

		if (cur_stage == TMP2 || cur_stage == BOTH)
			pop_as(s2, &tmp_s2);

		if (tmp_s1 < tmp_s2) {
			push_as(res_s, tmp_s1);
			cur_stage = TMP1;
		} else {
			push_as(res_s, tmp_s2);
			cur_stage = TMP2;
		}
	}

	if (cur_stage == TMP1)
		push_as(res_s, tmp_s2);

	if (cur_stage == TMP2)
		push_as(res_s, tmp_s1);

	while (s1->ps != -1) {
		pop_as(s1, &tmp_s1);
		push_as(res_s, tmp_s1);
	}

	while (s2->ps != -1) {
		pop_as(s2, &tmp_s2);
		push_as(res_s, tmp_s2);
	}

	return 0;
}


void 	g_rand_as(arr_stack_t *s, size_t n_els)
{
	srand(time(NULL));

	for (ssize_t i = 0; i < n_els; ++i)
		push_as(s, (rand() % (MAX_GEN_N * 2)) - MAX_GEN_N);
}


void g_rand_ls(list_stack_t *s, size_t n_els)
{
	srand(time(NULL));

	for (ssize_t i = 0; i < n_els; ++i)
		push_ls(s, (rand() % (MAX_GEN_N * 2)) - MAX_GEN_N);
}
