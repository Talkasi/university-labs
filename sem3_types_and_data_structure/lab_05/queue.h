#ifndef QUEUE_H
#define QUEUE_H
#include <stdio.h>

typedef enum {
	Q_IS_FULL = -10,
	Q_IS_EMPTY = -11,
	ALLOC_ERR,
} errs;

typedef enum {
	FIRST_A,
	SECOND_A,
	BOTH_A,
} stat_flag;

typedef enum {
	ARRAY,
	LIST
} queue_type;

typedef struct {
	char val;
	double entered_time;
} request_t;

#define EPS 10e-6
#define MAX_QUEUE_SIZE 5
#define MAX_N_REQUESTS 10

typedef struct {
	request_t q[MAX_QUEUE_SIZE];
	size_t p_read;
	size_t p_write;
	size_t n_requests;
} array_queue_t;

typedef struct node node_t;

struct node {
	request_t r;
	node_t *next;
};

typedef struct {
	node_t *head;
	size_t n_requests;
} list_queue_t;

typedef struct {
	double time_min;
	double time_max;

	double time_left;
	double free_time;
	double work_time;
	double prev_work_time;
	double request_time_sum;

	request_t r;
	size_t n_processed;
	double length_sum;
} machine_t;

int fill_list_queue(list_queue_t *q);
void free_list_queue(list_queue_t *q);

void array_process(array_queue_t *q1, array_queue_t *q2, machine_t *a1, machine_t *a2);
void list_process(list_queue_t *q1, list_queue_t *q2, machine_t *a1, machine_t *a2);

#endif