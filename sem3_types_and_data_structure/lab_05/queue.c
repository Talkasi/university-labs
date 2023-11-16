#include "queue.h"
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <math.h>

void update_stat(size_t n_requests_q1, size_t n_requests_q2, machine_t *a1, machine_t *a2, stat_flag f);
void print_short_info(size_t n_requests_q1, size_t n_requests_q2, machine_t *a1, machine_t *a2);
void print_all_info(machine_t *a1, machine_t *a2);

double	get_time(double t_min, double t_max)
{
	// NOTE(talkasi): srand should be called before somewhere else.
	return (t_max - t_min) * drand48() + t_min;
}


int	store_law()
{
	// NOTE(talkasi): srand should be called before somewhere else.
	return rand() % 10000 < 7000;
}

// NOTE(talkasi): Array part 
int	push_array(array_queue_t *q, request_t r)
{
	if (q->n_requests + 1 <= MAX_QUEUE_SIZE) {
		q->q[q->p_write++] = r;
		q->p_write %= MAX_QUEUE_SIZE;
		return ++q->n_requests;
	}

	return Q_IS_FULL;
}


int	pop_array(array_queue_t *q, request_t *r)
{
	if (q->n_requests != 0) {
		*r = q->q[q->p_read++];
		q->p_read %= MAX_QUEUE_SIZE;
		return --q->n_requests;
	}

	return Q_IS_EMPTY;
}

void array_store_by_law(array_queue_t *q1, array_queue_t *q2, machine_t *a1, machine_t *a2)
{
	a1->r.entered_time = a1->work_time;
	if (store_law())
		assert(push_array(q1, a1->r) >= 0);
	else
		assert(push_array(q2, a1->r) >= 0);
}

void array_handle_simultaneous(array_queue_t *q1, array_queue_t *q2, machine_t *a1, machine_t *a2)
{
	if (fabs(a1->time_left - a2->time_left) < EPS) {
		a2->r.entered_time = a1->work_time;
		assert(push_array(q1, a2->r) >= 0);
		array_store_by_law(q1, q2, a1, a2);
		update_stat(q1->n_requests, q2->n_requests, a1, a2, BOTH_A);
	} else if (a1->time_left > a2->time_left) {
		a2->r.entered_time = a1->work_time;
		assert(push_array(q1, a2->r) >= 0);
		update_stat(q1->n_requests, q2->n_requests, a1, a2, SECOND_A);
	} else {
		array_store_by_law(q1, q2, a1, a2);
		update_stat(q1->n_requests, q2->n_requests, a1, a2, FIRST_A);
	}
}

void array_process(array_queue_t *q1, array_queue_t *q2, machine_t *a1, machine_t *a2)
{
	srand48(time(NULL));
	srand(time(NULL));

	size_t prev = 0;
	while (a2->n_processed < MAX_N_REQUESTS) {
		assert(q1->n_requests > 0);

		/* NOTE(Talkasi): The second queue is empty, no machine is working. */
		if (q2->n_requests == 0 && a1->time_left < EPS && a2->time_left < EPS) {
			assert(pop_array(q1, &a1->r) >= 0);
			a1->request_time_sum += a1->work_time - a1->r.entered_time;

			a1->time_left = get_time(a1->time_min, a1->time_max);
			a1->work_time += a1->time_left;
			a1->length_sum += q1->n_requests * a1->time_left;
			array_store_by_law(q1, q2, a1, a2);

			++a1->n_processed;
			a1->time_left = 0;
		}

		/* NOTE(Talksi): Both queues are not empty, no machine is working. */
		else if (q2->n_requests != 0 && a1->time_left < EPS && a2->time_left < EPS) {
			assert(pop_array(q1, &a1->r) >= 0);
			a1->request_time_sum += a1->work_time - a1->r.entered_time;
			a1->time_left = get_time(a1->time_min, a1->time_max);

			a2->free_time += a1->work_time - a2->prev_work_time;

			assert(pop_array(q2, &a2->r) >= 0);
			a2->request_time_sum += a1->work_time - a2->r.entered_time;
			a2->time_left = get_time(a2->time_min, a2->time_max);
			a2->prev_work_time = a1->work_time + a2->time_left;

			array_handle_simultaneous(q1, q2, a1, a2);
		}
		
		/* NOTE(Talkasi): The first machine is not working, the second does. */
		else if (a2->time_left >= EPS && a1->time_left < EPS) {
			assert(pop_array(q1, &a1->r) >= 0);
			a1->request_time_sum += a1->work_time - a2->r.entered_time;

			a1->time_left = get_time(a1->time_min, a1->time_max);

			array_handle_simultaneous(q1, q2, a1, a2);
		}

		/* NOTE(Talkasi): The first machine is working, the second doesn't.
		 * The second queue is empty.
		 */
		else if (a1->time_left > EPS && a2->time_left < EPS && q2->n_requests == 0) {
			array_store_by_law(q1, q2, a1, a2);

			++a1->n_processed;
			a1->length_sum += q1->n_requests * a1->time_left;
			a2->length_sum += q2->n_requests * a1->time_left;

			a1->work_time += a1->time_left;
			a1->time_left = 0;
		}

		/* NOTE(Talkasi): The first machine is working, the second doesn't.
		 * The second queue is not empty.
		 */
		else if (a1->time_left > EPS && a2->time_left < EPS && q2->n_requests != 0) {
			a2->free_time += a1->work_time - a2->prev_work_time;

			assert(pop_array(q2, &a2->r) >= 0);
			a2->request_time_sum += a1->work_time - a2->r.entered_time;
			a2->time_left = get_time(a2->time_min, a2->time_max);
			a2->prev_work_time = a1->work_time + a2->time_left;

			array_handle_simultaneous(q1, q2, a1, a2);
		}

		if (prev != a2->n_processed && a2->n_processed % MAX_QUEUE_SIZE == 0) {
			prev = a2->n_processed;
			print_short_info(q1->n_requests, q2->n_requests, a1, a2);
		}
	}

	print_all_info(a1, a2);
}

int push_list(list_queue_t *q, request_t r)
{
	node_t *tmp = malloc(sizeof(node_t));
	if (tmp == NULL)
		return ALLOC_ERR;

	tmp->r.val = r.val;
	tmp->r.entered_time = r.entered_time;
	tmp->next = NULL;

	++q->n_requests;

	node_t *cur_node = q->head;
	if (cur_node == NULL) {
		q->head = tmp;
		return 0;
	}

	while (cur_node->next != NULL)
		cur_node = cur_node->next;

	cur_node->next = tmp;
	return 0;
}

// NOTE(Talkasi): Node is dinamically allocated, but request is NOT.
int pop_list(list_queue_t *q, request_t *r)
{
	if (q->head != NULL) {
		*r = q->head->r;

		--q->n_requests;
		node_t *tmp = q->head;
		q->head = q->head->next;

		// TODO(Talkasi): Check this with valgrind!
		free(tmp);
		return 0;
	}

	return Q_IS_EMPTY;
}


int fill_list_queue(list_queue_t *q) {
	int rc;
	request_t r = {'\0', 0};

	for (size_t i = 0; i < MAX_QUEUE_SIZE; ++i)
		if ((rc = push_list(q, r)) < 0)
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


void list_store_by_law(list_queue_t *q1, list_queue_t *q2, machine_t *a1, machine_t *a2)
{
	a1->r.entered_time = a1->work_time;
	if (store_law())
		assert(push_list(q1, a1->r) >= 0);
	else
		assert(push_list(q2, a1->r) >= 0);
}

void list_handle_simultaneous(list_queue_t *q1, list_queue_t *q2, machine_t *a1, machine_t *a2)
{
	if (fabs(a1->time_left - a2->time_left) < EPS) {
		a2->r.entered_time = a1->work_time;
		assert(push_list(q1, a2->r) >= 0);
		list_store_by_law(q1, q2, a1, a2);
		update_stat(q1->n_requests, q2->n_requests, a1, a2, BOTH_A);
	} else if (a1->time_left > a2->time_left) {
		a2->r.entered_time = a1->work_time;
		assert(push_list(q1, a2->r) >= 0);
		update_stat(q1->n_requests, q2->n_requests, a1, a2, SECOND_A);
	} else {
		list_store_by_law(q1, q2, a1, a2);
		update_stat(q1->n_requests, q2->n_requests, a1, a2, FIRST_A);
	}
}


void list_process(list_queue_t *q1, list_queue_t *q2, machine_t *a1, machine_t *a2)
{
	srand48(time(NULL));
	srand(time(NULL));

	size_t prev = 0;
	while (a2->n_processed < MAX_N_REQUESTS) {
		assert(q1->n_requests > 0);

		/* NOTE(Talkasi): The second queue is empty, no machine is working. */
		if (q2->n_requests == 0 && a1->time_left < EPS && a2->time_left < EPS) {
			assert(pop_list(q1, &a1->r) >= 0);
			a1->request_time_sum += a1->work_time - a1->r.entered_time;

			a1->time_left = get_time(a1->time_min, a1->time_max);
			a1->work_time += a1->time_left;
			a1->length_sum += q1->n_requests * a1->time_left;
			list_store_by_law(q1, q2, a1, a2);

			++a1->n_processed;
			a1->time_left = 0;
		}

		/* NOTE(Talksi): Both queues are not empty, no machine is working. */
		else if (q2->n_requests != 0 && a1->time_left < EPS && a2->time_left < EPS) {
			assert(pop_list(q1, &a1->r) >= 0);
			a1->request_time_sum += a1->work_time - a1->r.entered_time;
			a1->time_left = get_time(a1->time_min, a1->time_max);

			a2->free_time += a1->work_time - a2->prev_work_time;

			assert(pop_list(q2, &a2->r) >= 0);
			a2->request_time_sum += a1->work_time - a2->r.entered_time;
			a2->time_left = get_time(a2->time_min, a2->time_max);
			a2->prev_work_time = a1->work_time + a2->time_left;

			list_handle_simultaneous(q1, q2, a1, a2);
		}
		
		/* NOTE(Talkasi): The first machine is not working, the second does. */
		else if (a2->time_left >= EPS && a1->time_left < EPS) {
			assert(pop_list(q1, &a1->r) >= 0);
			a1->request_time_sum += a1->work_time - a2->r.entered_time;

			a1->time_left = get_time(a1->time_min, a1->time_max);

			list_handle_simultaneous(q1, q2, a1, a2);
		}

		/* NOTE(Talkasi): The first machine is working, the second doesn't.
		 * The second queue is empty.
		 */
		else if (a1->time_left > EPS && a2->time_left < EPS && q2->n_requests == 0) {
			list_store_by_law(q1, q2, a1, a2);

			++a1->n_processed;
			a1->length_sum += q1->n_requests * a1->time_left;
			a2->length_sum += q2->n_requests * a1->time_left;

			a1->work_time += a1->time_left;
			a1->time_left = 0;
		}

		/* NOTE(Talkasi): The first machine is working, the second doesn't.
		 * The second queue is not empty.
		 */
		else if (a1->time_left > EPS && a2->time_left < EPS && q2->n_requests != 0) {
			a2->free_time += a1->work_time - a2->prev_work_time;

			assert(pop_list(q2, &a2->r) >= 0);
			a2->request_time_sum += a1->work_time - a2->r.entered_time;
			a2->time_left = get_time(a2->time_min, a2->time_max);
			a2->prev_work_time = a1->work_time + a2->time_left;

			list_handle_simultaneous(q1, q2, a1, a2);
		}

		if (prev != a2->n_processed && a2->n_processed % MAX_QUEUE_SIZE == 0) {
			prev = a2->n_processed;
			print_short_info(q1->n_requests, q2->n_requests, a1, a2);
		}
	}

	print_all_info(a1, a2);
}

void update_stat(size_t n_requests_q1, size_t n_requests_q2, machine_t *a1, machine_t *a2, stat_flag f) {
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
}

void print_short_info(size_t n_requests_q1, size_t n_requests_q2, machine_t *a1, machine_t *a2)
{
	/*
Выдавать на экран после обслуживания в ОА2 каждых 100 заявок
информацию о текущей и средней длине каждой очереди,

а в конце процесса -
общее время моделирования,
время простоя ОА2,
количество срабатываний ОА1,
среднее времени пребывания заявок в очереди.

Обеспечить по
требованию пользователя выдачу на экран адресов элементов очереди при
удалении и добавлении элементов.
	*/
	printf(">> PROCESSED: %zu requests\n", a2->n_processed);
	printf("%-35s %10zu\n", "Length of the first queue:", n_requests_q1);
	printf("%-35s %10lf\n", "Average length of the first queue:",
	    (double) a1->length_sum / a1->work_time);
	printf("%-35s %10zu\n", "Length of the second queue:", n_requests_q2);
	printf("%-35s %10lf\n\n", "Average length of the second queue:",
	    (double) a2->length_sum / a1->work_time);
}


void print_all_info(machine_t *a1, machine_t *a2)
{
	printf(">> RESULT:\n");
	printf("%-60s %12lf\n", "Work time:", a1->work_time);
	printf("%-60s %12lf %12lf\n", "Free time of the second machine:", a2->free_time, a1->work_time - a2->work_time);
	printf("%-60s %12zu\n", "Number of requests processed by the first machine:",
	    a1->n_processed);
	printf("%-60s %12lf\n", "Average time for the requests to stay in the first queue:",
	    a1->request_time_sum / a1->n_processed);
	printf("%-60s %12lf\n\n", "Average time for the requests to stay in the second queue:",
	    a2->request_time_sum / a2->n_processed);
}


