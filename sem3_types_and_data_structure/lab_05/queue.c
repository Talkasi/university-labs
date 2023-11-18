#include "queue.h"
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <math.h>

void print_header()
{
	printf("┌─────────────┬─────────────────────────────────┬─────────────────────────────────┐\n"
	       "│ Number of   │            First queue          │          Second queue           │\n"
	       "│ requests    ├────────────────┬────────────────┼────────────────┬────────────────┤\n"
		   "│ processed   │ Current length │ Average length │ Current length │ Average length │\n"
	       "├─────────────┼────────────────┼────────────────┼────────────────┼────────────────┤\n");
}

void print_short_info(size_t q1_n_requests, size_t q2_n_requests, machine_t *a1, machine_t *a2, double total_work_time)
{
	printf("│ %11zu │ %14zu │ %14lf │ %14zu │ %14lf │\n", a2->n_processed, 
		   q1_n_requests, (double) a1->length_sum / total_work_time,
		   q2_n_requests, (double) a2->length_sum / total_work_time);
}

void print_footer()
{
	printf("└─────────────┴────────────────┴────────────────┴────────────────┴────────────────┘\n");
}


void print_all_info(machine_t *a1, machine_t *a2, double total_work_time)
{
	printf(">>  RESULT:\n");
	printf("│ %-60s %12lf\n", "Work time:", total_work_time);
	printf("│ %-60s %12lf\n", "Free time of the second machine:", total_work_time - a2->work_time);
	printf("│ %-60s %12zu\n", "Number of requests processed by the first machine:",
	    a1->n_processed);
	printf("│ %-60s %12lf\n", "Average time for the requests to stay in the first queue:",
	    a1->request_time_sum / a1->n_processed);
	printf("│ %-60s %12lf\n│ \n", "Average time for the requests to stay in the second queue:",
	    a2->request_time_sum / a2->n_processed);
}

// NOTE(talkasi): Array part 
int	push_array(queue_t *q, request_t r)
{
	array_queue_t *Q = (array_queue_t *)q;

	if (Q->n_requests + 1 <= MAX_QUEUE_SIZE) {
		Q->q[Q->p_write++] = r;
		Q->p_write %= MAX_QUEUE_SIZE;
		return ++Q->n_requests;
	}

	return Q_IS_FULL;
}


int	pop_array(queue_t *q, request_t *r)
{
	array_queue_t *Q = (array_queue_t *)q;

	if (Q->n_requests != 0) {
		*r = Q->q[Q->p_read++];
		Q->p_read %= MAX_QUEUE_SIZE;
		return --Q->n_requests;
	}

	return Q_IS_EMPTY;
}

size_t array_get_n_requests(queue_t *q)
{
	array_queue_t *Q = (array_queue_t *)q;
	return Q->n_requests;
}

int push_list(queue_t *q, request_t r)
{
	list_queue_t *Q = (list_queue_t *)q;

	node_t *tmp = malloc(sizeof(node_t));
	if (tmp == NULL)
		return ALLOC_ERR;

	tmp->r.val = r.val;
	tmp->r.entered_time = r.entered_time;
	tmp->next = NULL;

	++Q->n_requests;

	node_t *cur_node = Q->head;
	if (cur_node == NULL) {
		Q->head = tmp;
		return 0;
	}

	while (cur_node->next != NULL)
		cur_node = cur_node->next;

	cur_node->next = tmp;
	return 0;
}

// NOTE(Talkasi): Node is dinamically allocated, but request is NOT.
int pop_list(queue_t *q, request_t *r)
{
	list_queue_t *Q = (list_queue_t *)q;

	if (Q->head != NULL) {
		*r = Q->head->r;

		--Q->n_requests;
		node_t *tmp = Q->head;
		Q->head = Q->head->next;

		free(tmp);
		return 0;
	}

	return Q_IS_EMPTY;
}

size_t list_get_n_requests(queue_t *q)
{
	list_queue_t *Q = (list_queue_t *)q;
	return Q->n_requests;
}


int fill_list_queue(list_queue_t *q) {
	int rc;
	request_t r = {'\0', 0};

	for (size_t i = 0; i < MAX_QUEUE_SIZE; ++i)
		if ((rc = push_list((queue_t *)q, r)) < 0)
			return rc;

	return 0;
}


void free_list_queue(list_queue_t *q) {
	node_t *cur_node = q->head;
	while (cur_node != NULL) {
		node_t *tmp = cur_node->next;
		free(cur_node);
		cur_node = tmp;
	}
}


double	get_time(double t_min, double t_max)
{
	// NOTE(talkasi): srand should be called before somewhere else.
	return (t_max - t_min) * drand48() + t_min;
}


int	push_law(double possibility)
{
	// NOTE(talkasi): srand should be called before somewhere else.
	return rand() % ACCURACY < possibility * ACCURACY;
}

void push_by_law(queue_t *q1, queue_t *q2, machine_t *a1, machine_t *a2, double possibility)
{
	if (push_law(possibility))
		assert(q1->Push(q1, a1->r) >= 0);
	else
		assert(q2->Push(q2, a1->r) >= 0);
}


void update_stat(size_t n_requests_q1, size_t n_requests_q2, 
				 machine_t *a1, machine_t *a2, 
				 double *total_work_time, stat_flag f) {
	double time_left;

	switch (f) {
	case FIRST_A:
		time_left = a1->time_left;
		++a1->n_processed;

		a1->time_left = 0;
		a2->time_left -= time_left;
		break;
	case SECOND_A:
		time_left = a2->time_left;
		++a2->n_processed;

		a1->time_left -= time_left;
		a2->time_left = 0;
		break;
	case BOTH_A:
		time_left = a1->time_left;
		++a1->n_processed;
		++a2->n_processed;

		a1->time_left = 0;
		a2->time_left = 0;
		break;
	}

	a1->length_sum += n_requests_q1 * time_left;
	a2->length_sum += n_requests_q2 * time_left;

	a1->work_time += time_left;
	a2->work_time += time_left;

	*total_work_time += time_left;
}


void handle_simultaneous(queue_t *q1, queue_t *q2, 
						 machine_t *a1, machine_t *a2, 
						 double *total_work_time, double possibility)
{
	if (fabs(a1->time_left - a2->time_left) < EPS) {
		a2->r.entered_time = *total_work_time;
		assert(q1->Push(q1, a2->r) >= 0);

		a1->r.entered_time = *total_work_time;
		push_by_law(q1, q2, a1, a2, possibility);

		update_stat(q1->Get_n_requests(q1), q2->Get_n_requests(q2), a1, a2, total_work_time, BOTH_A);
	} else if (a1->time_left > a2->time_left) {
		a2->r.entered_time = *total_work_time;
		assert(q1->Push(q1, a2->r) >= 0);

		update_stat(q1->Get_n_requests(q1), q2->Get_n_requests(q2), a1, a2, total_work_time, SECOND_A);
	} else {
		a1->r.entered_time = *total_work_time;
		push_by_law(q1, q2, a1, a2, possibility);

		update_stat(q1->Get_n_requests(q1), q2->Get_n_requests(q2), a1, a2, total_work_time, FIRST_A);
	}
}


void	process(queue_t *q1, queue_t *q2, machine_t *a1, machine_t *a2, double possibility)
{
	srand48(time(NULL));
	srand(time(NULL));

	double total_work_time = 0;

	size_t prev = 0;
	while (a2->n_processed < MAX_N_REQUESTS) {
		/* NOTE(Talkasi): The first queue is empty. No machine is working. */
		if (q1->Get_n_requests(q1) == 0 && a1->time_left < EPS && a2->time_left < EPS) {
			assert(q2->Pop(q2, &a2->r) >= 0);
			a2->request_time_sum += total_work_time - a2->r.entered_time;

			a2->time_left = get_time(a2->time_min, a2->time_max);
			total_work_time += a2->time_left;
			a2->work_time += a2->time_left;

			a2->length_sum += q2->Get_n_requests(q2) * a2->time_left;

			a2->r.entered_time = total_work_time;
			assert(q1->Push(q1, a2->r) >= 0);

			++a2->n_processed;
			a2->time_left = 0;
		}

		/* NOTE(Talkasi): The first queue is empty. The second machine is working, 
		 * the first doesn't. 
		 */
		else if (q1->Get_n_requests(q1) == 0 && a1->time_left < EPS && a2->time_left >= EPS) {
			total_work_time += a2->time_left;
			a2->work_time += a2->time_left;
			a2->length_sum += q2->Get_n_requests(q2) * a2->time_left;

			a2->r.entered_time = total_work_time;
			assert(q1->Push(q1, a2->r) >= 0);

			++a2->n_processed;
			a2->time_left = 0;
		}

		/* NOTE(Talkasi): The first queue is empty, the second is not. 
		 * The first machine is working, the second doesn't. 
		 */
		else if (q1->Get_n_requests(q1) == 0 && a1->time_left >= EPS && a2->time_left < EPS) {
			assert(q2->Pop(q2, &a2->r) >= 0);
			a2->request_time_sum += total_work_time - a2->r.entered_time;

			a2->time_left = get_time(a2->time_min, a2->time_max);

			handle_simultaneous(q1, q2, a1, a2, &total_work_time, possibility);
		}

		/* NOTE(Talkasi): The second queue is empty, no machine is working. */
		else if (q2->Get_n_requests(q2) == 0 && a1->time_left < EPS && a2->time_left < EPS) {
			assert(q1->Pop(q1, &a1->r) >= 0);
			a1->request_time_sum += total_work_time - a1->r.entered_time;

			a1->time_left = get_time(a1->time_min, a1->time_max);
			total_work_time += a1->time_left;
			a1->work_time += a1->time_left;

			a1->length_sum += q1->Get_n_requests(q1) * a1->time_left;

			a1->r.entered_time = total_work_time;
			push_by_law(q1, q2, a1, a2, possibility);

			++a1->n_processed;
			a1->time_left = 0;
		}

		/* NOTE(Talksi): Both queues are not empty, no machine is working. */
		else if (q1->Get_n_requests(q1) != 0 && q2->Get_n_requests(q2) != 0 &&
				 a1->time_left < EPS && a2->time_left < EPS) {
			assert(q1->Pop(q1, &a1->r) >= 0);
			a1->request_time_sum += total_work_time - a1->r.entered_time;
			a1->time_left = get_time(a1->time_min, a1->time_max);

			assert(q2->Pop(q2, &a2->r) >= 0);
			a2->request_time_sum += total_work_time - a2->r.entered_time;
			a2->time_left = get_time(a2->time_min, a2->time_max);

			handle_simultaneous(q1, q2, a1, a2, &total_work_time, possibility);
		}

		/* NOTE(Talkasi): The first machine is not working, the second does. 
		 * The first queue is not empty.
		 */
		else if (q1->Get_n_requests(q1) != 0 && a2->time_left >= EPS && a1->time_left < EPS) {
			assert(q1->Pop(q1, &a1->r) >= 0);
			a1->request_time_sum += total_work_time - a2->r.entered_time;
			a1->time_left = get_time(a1->time_min, a1->time_max);

			handle_simultaneous(q1, q2, a1, a2, &total_work_time, possibility);
		}

		/* NOTE(Talkasi): The first machine is working, the second doesn't.
		 * The second queue is empty.
		 */
		else if (a1->time_left >= EPS && a2->time_left < EPS && q2->Get_n_requests(q2) == 0) {
			a1->r.entered_time = total_work_time;
			push_by_law(q1, q2, a1, a2, possibility);

			++a1->n_processed;
			a1->length_sum += q1->Get_n_requests(q1) * a1->time_left;
			a2->length_sum += q2->Get_n_requests(q2) * a1->time_left;

			total_work_time += a1->time_left;
			a1->work_time += a1->time_left;
			a1->time_left = 0;
		}

		/* NOTE(Talkasi): The first machine is working, the second doesn't.
		 * The second queue is not empty.
		 */
		else if (a1->time_left >= EPS && a2->time_left < EPS && 
				 q1->Get_n_requests(q1) != 0 && q2->Get_n_requests(q2) != 0) {

			assert(q2->Pop(q2, &a2->r) >= 0);
			a2->request_time_sum += total_work_time - a2->r.entered_time;
			a2->time_left = get_time(a2->time_min, a2->time_max);

			handle_simultaneous(q1, q2, a1, a2, &total_work_time, possibility);
		}

		if (prev != a2->n_processed && a2->n_processed % MAX_QUEUE_SIZE == 0) {
			if (prev == 0)
				print_header();

			prev = a2->n_processed;
			print_short_info(q1->Get_n_requests(q1), q2->Get_n_requests(q2), a1, a2, total_work_time);
		}
	}

	print_footer();
	print_all_info(a1, a2, total_work_time);
}
