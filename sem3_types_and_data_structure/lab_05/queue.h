#ifndef QUEUE_H
#define QUEUE_H
#include <stdio.h>

enum errs {
	Q_IS_FULL = -10,
	Q_IS_EMPTY = -11,
	ALLOC_ERR
};

typedef enum {
	FIRST_A,
	SECOND_A,
	BOTH_A,
} stat_flag;

#define RED "\033[0;31m"
#define GREEN "\033[0;32m"
#define YELLOW "\033[0;33m"
#define BLUE "\033[0;34m"
#define PIRPLE "\033[0;35m"
#define CYAN "\033[0;36m"
#define NC "\033[0m"

#define EPS 10e-6
#define MAX_QUEUE_SIZE 100
#define MAX_N_REQUESTS 1000
#define ACCURACY 10000

typedef struct node node_t;
typedef struct queue queue_t;
typedef struct request request_t;

typedef int (*push)(queue_t *, request_t r);
typedef int (*pop)(queue_t *, request_t *r);
typedef size_t (*get_n_requests)(queue_t *);

struct request {
	char val;
	double entered_time;
};

struct node {
	request_t r;
	node_t *next;
};

struct queue {
	push Push;
	pop Pop;
	get_n_requests Get_n_requests;
};

typedef struct {
	push Push;
	pop Pop;
	get_n_requests Get_n_requests;

	request_t q[MAX_QUEUE_SIZE];
	size_t p_read;
	size_t p_write;
	size_t n_requests;
} array_queue_t;

typedef struct {
	push Push;
	pop Pop;
	get_n_requests Get_n_requests;

	node_t *head;
	size_t n_requests;
} list_queue_t;

typedef struct {
	double time_min;
	double time_max;

	double time_left;
	double work_time;
	double request_time_sum;

	request_t r;
	size_t n_processed;
	double length_sum;
} machine_t;

int	push_array(queue_t *q, request_t r);
int	pop_array(queue_t *q, request_t *r);
size_t array_get_n_requests(queue_t *q);

int push_list(queue_t *q, request_t r);
int pop_list(queue_t *q, request_t *r);
size_t list_get_n_requests(queue_t *q);

int fill_list_queue(list_queue_t *q);
void free_list_queue(list_queue_t *q);

void	process(queue_t *q1, queue_t *q2, machine_t *a1, machine_t *a2, double possibility);

#define CREATE_ARRAY_QUEUE(q) array_queue_t q = {push_array, pop_array, array_get_n_requests}
#define CREATE_LIST_QUEUE(q) list_queue_t q = {push_list, pop_list, list_get_n_requests}

#define INIT_ARRAY_QUEUE(q) q->Push = push_array, q->Pop = pop_array, q->Get_n_requests = array_get_n_requests
#define INIT_LIST_QUEUE(q) q->Push = push_list, q->Pop = pop_list, q->Get_n_requests = list_get_n_requests

#endif