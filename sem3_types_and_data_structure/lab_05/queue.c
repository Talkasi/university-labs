#include "queue.h"
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <math.h>

void print_short_info(machine_t *a1, machine_t *a2);
void print_all_info(machine_t *a1, machine_t *a2);

int	push(q_t *q, request_t r)
{
	if (q->n_requests + 1 <= MAX_QUEUE_SIZE) {
		q->q[q->p_write++] = r;
		q->p_write %= MAX_QUEUE_SIZE;
		return ++q->n_requests;
	}

	return Q_IS_FULL;
}


int	pop(q_t *q, request_t *r)
{
	if (q->n_requests != 0) {
		*r = q->q[q->p_read++];
		q->p_read %= MAX_QUEUE_SIZE;
		return --q->n_requests;
	}

	return Q_IS_EMPTY;
}



double	get_time(double t_min, double t_max)
{
	// NOTE(talkasi): srand should be called before somewhere else.
	return (t_max - t_min) * drand48() + t_min;
}


int	store_law()
{
	int	a = rand();
	//printf("%d\n", a % 10000);
	return a % 10000 < 7000;
}


void store_by_law(machine_t *a1, machine_t *a2)
{
	a1->r.entered_time = a1->work_time;
	if (store_law())
		assert(push(&a1->q, a1->r) >= 0);
	else
		assert(push(&a2->q, a1->r) >= 0);
}


void handle_simultaneous(machine_t *a1, machine_t *a2)
{
	if (fabs(a1->time_left - a2->time_left) < EPS) {
		a2->r.entered_time = a1->work_time;
		assert(push(&a1->q, a2->r) >= 0);
		store_by_law(a1, a2);

		++a1->n_processed;
		++a2->n_processed;
		a1->length_sum += a1->q.n_requests * a1->time_left;
		a2->length_sum += a2->q.n_requests * a1->time_left;

		a1->work_time += a1->time_left;
		a2->work_time += a1->time_left;

		a1->time_left = 0;
		a2->time_left = 0;
	} else if (a1->time_left > a2->time_left) {
		a2->r.entered_time = a1->work_time;
		assert(push(&a1->q, a2->r) >= 0);

		++a2->n_processed;
		a1->length_sum += a1->q.n_requests * a2->time_left;
		a2->length_sum += a2->q.n_requests * a2->time_left;

		a1->work_time += a2->time_left;
		a2->work_time += a2->time_left;

		a1->time_left -= a2->time_left;
		a2->time_left = 0;
	} else {
		store_by_law(a1, a2);

		++a1->n_processed;
		a1->length_sum += a1->q.n_requests * a1->time_left;
		a2->length_sum += a2->q.n_requests * a1->time_left;

		a1->work_time += a1->time_left;
		a2->work_time += a1->time_left;

		a2->time_left -= a1->time_left;
		a1->time_left = 0;
	}
}


void	process(machine_t *a1, machine_t *a2)
{
	srand48(time(NULL));
	srand(time(NULL));

	size_t prev = 0;
	while (a2->n_processed < MAX_N_REQUESTS) {
		/*
			q 1 q 2
			1 0 0 0 done DEF
			1 0 0 1 done DEF
			1 0 1 0 done DEF
			1 0 1 1 done DEF
			1 1 0 0 done DEF
			1 1 0 1 <-     Impossible.
			1 1 1 0 done DEF
			1 1 1 1 <-     Impossible.

		*/
		assert(a1->q.n_requests > 0);

		/* NOTE(Talkasi): The second queue is empty, no machine is working. */
		if (a2->q.n_requests == 0 && a1->time_left < EPS && a2->time_left < EPS) {
			assert(pop(&a1->q, &a1->r) >= 0);
			a1->request_time_sum += a1->work_time - a1->r.entered_time;

			a1->time_left = get_time(a1->time_min, a1->time_max);
			a1->work_time += a1->time_left;
			a1->length_sum += a1->q.n_requests * a1->time_left;
			store_by_law(a1, a2);

			++a1->n_processed;
			a1->time_left = 0;
		}

		/* NOTE(Talksi): Both queues are not empty, no machine is working. */
		else if (a2->q.n_requests != 0 && a1->time_left < EPS && a2->time_left < EPS) {
			assert(pop(&a1->q, &a1->r) >= 0);
			a1->request_time_sum += a1->work_time - a1->r.entered_time;
			a1->time_left = get_time(a1->time_min, a1->time_max);

			a2->free_time += a1->work_time - a2->prev_work_time;

			assert(pop(&a2->q, &a2->r) >= 0);
			a2->request_time_sum += a1->work_time - a2->r.entered_time;
			a2->time_left = get_time(a2->time_min, a2->time_max);
			a2->prev_work_time = a1->work_time + a2->time_left;

			handle_simultaneous(a1, a2);
		}
		
		/* NOTE(Talkasi): The first machine is not working, the second does. */
		else if (a2->time_left >= EPS && a1->time_left < EPS) {
			assert(pop(&a1->q, &a1->r) >= 0);
			a1->request_time_sum += a1->work_time - a2->r.entered_time;

			a1->time_left = get_time(a1->time_min, a1->time_max);

			handle_simultaneous(a1, a2);
		}
		/* NOTE(Talkasi): The first machine is working, the second doesn't.
		 * The second queue is empty.
		 */
		else if (a1->time_left > EPS && a2->time_left < EPS && a2->q.n_requests == 0) {
			store_by_law(a1, a2);

			++a1->n_processed;
			a1->length_sum += a1->q.n_requests * a1->time_left;
			a2->length_sum += a2->q.n_requests * a1->time_left;

			a1->work_time += a1->time_left;
			a1->time_left = 0;
		}
		/* NOTE(Talkasi): The first machine is working, the second doesn't.
		 * The second queue is not empty.
		 */
		else if (a1->time_left > EPS && a2->time_left < EPS && a2->q.n_requests != 0) {
			a2->free_time += a1->work_time - a2->prev_work_time;

			assert(pop(&a2->q, &a2->r) >= 0);
			a2->request_time_sum += a1->work_time - a2->r.entered_time;
			a2->time_left = get_time(a2->time_min, a2->time_max);
			a2->prev_work_time = a1->work_time + a2->time_left;

			handle_simultaneous(a1, a2);
		}

		if (prev != a2->n_processed && a2->n_processed % MAX_QUEUE_SIZE == 0) {
			prev = a2->n_processed;
			print_short_info(a1, a2);
		}
	}

	print_all_info(a1, a2);
}


void print_short_info(machine_t *a1, machine_t *a2)
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
	printf("%-35s %10zu\n", "Length of the first queue:", a1->q.n_requests);
	printf("%-35s %10lf\n", "Average length of the first queue:",
	    (double) a1->length_sum / a1->work_time);
	printf("%-35s %10zu\n", "Length of the second queue:", a2->q.n_requests);
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


