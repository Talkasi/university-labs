#ifndef QUEUE_H
#define QUEUE_H
#include <stdio.h>

enum errs {
	Q_IS_FULL = -10,
	Q_IS_EMPTY
};

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
} q_t;

typedef struct {
	double time_min;
	double time_max;

	double time_left;
	double free_time;
	double work_time;
	double prev_work_time;
	double request_time_sum;

	q_t q;
	request_t r;
	size_t n_processed;
	double length_sum;
} machine_t;

void	process(machine_t *a1, machine_t *a2);

#endif