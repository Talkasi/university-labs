#include "queue.h"
#include "input.h"
#include <stdio.h>
#include <string.h>

enum commands {
	EXIT,
	CHANGE_QUEUE1_TIME,
	CHANGE_QUEUE2_TIME,
	CHANGE_POSSIBILITY,
	PROCESS_ARR_VAR,
	PROCESS_LIST_VAR
};

typedef struct {
	double time1_min;
	double time1_max;

	double time2_min;
	double time2_max;

	double possibility;
} settings_t;

#define DEFAULT_QUEUE_1_MIN_TIME 0
#define DEFAULT_QUEUE_1_MAX_TIME 6

#define DEFAULT_QUEUE_2_MIN_TIME 1
#define DEFAULT_QUEUE_2_MAX_TIME 8

#define DEFAULT_POSSIBILITY 0.7

#define CREATE_DEFAULT_SETTINGS(s) settings_t s = {DEFAULT_QUEUE_1_MIN_TIME, \
												   DEFAULT_QUEUE_1_MAX_TIME, \
												   DEFAULT_QUEUE_2_MIN_TIME, \
												   DEFAULT_QUEUE_2_MAX_TIME, \
												   DEFAULT_POSSIBILITY}

void pre_init_all(array_queue_t *array_q1, array_queue_t *array_q2,
				  list_queue_t *list_q1, list_queue_t *list_q2,
				  machine_t *a1, machine_t *a2, settings_t settings);

int	main(void)
{
	CREATE_DEFAULT_SETTINGS(settings);

	machine_t a1;
	machine_t a2;

	CREATE_ARRAY_QUEUE(array_q1);
	CREATE_ARRAY_QUEUE(array_q2);

	CREATE_LIST_QUEUE(list_q1);
	CREATE_LIST_QUEUE(list_q2);

	int command = -1;
	while (command != EXIT) {
		printf(CYAN "Menu:\n");
		printf("0 - Exit\n"
			   "1 - Change time boundaries for the first machine\n"
			   "2 - Change time boundaries for the second machine\n"
			   "3 - Change possibility for the request to enter the second queue\n"
			   "4 - Start simulation with array queues\n"
			   "5 - Start simulation with list queues\n" NC);
		printf(PIRPLE "> Enter number of the command to excecute: " NC);
		if (read_int(&command) || command < 0) {
			printf(RED "Wrong number." NC " Please, try again.\n");
			continue;
		}

		switch (command) {
		case EXIT:
			break;
		case CHANGE_QUEUE1_TIME:
			printf("Enter minimum time border of the first queue (double): ");
			while (read_double(&settings.time1_min) || settings.time1_min < 0)
				printf(RED "Wrong time border." NC " Try again: ");
			
			printf("Enter maximum time border of the first queue (double): ");
			while (read_double(&settings.time1_max) || settings.time1_max < 0 ||
				   settings.time1_max < settings.time1_min)
				printf(RED "Wrong time border." NC " Try again: ");
			break;
		case CHANGE_QUEUE2_TIME:
			printf("Enter minimum time border of the second queue (double): ");
			while (read_double(&settings.time2_min) || settings.time2_min < 0)
				printf(RED "Wrong time border." NC " Try again: ");
			
			printf("Enter maximum time border of the second queue (double): ");
			while (read_double(&settings.time2_max) || settings.time2_max < 0 ||
				   settings.time2_max < settings.time2_min)
				printf(RED "Wrong time border." NC " Try again: ");
			break;
		case CHANGE_POSSIBILITY:
			printf("Enter possibility for the request to stay in the first queue in [0, 1]: ");
			while (read_double(&settings.possibility) || settings.possibility < 0 ||
				   settings.possibility > 1)
				printf(RED "Wrong possibility." NC " It must be number from 0 to 1. Try again: ");
			break;
		case PROCESS_ARR_VAR:
			pre_init_all(&array_q1, &array_q2, &list_q1, &list_q2, &a1, &a2, settings);
			process((queue_t *)&array_q1, (queue_t *)&array_q2, &a1, &a2, settings.possibility);
			break;
		case PROCESS_LIST_VAR:
			pre_init_all(&array_q1, &array_q2, &list_q1, &list_q2, &a1, &a2, settings);
			process((queue_t *)&list_q1, (queue_t *)&list_q2, &a1, &a2, settings.possibility);
			break;
		default:
			printf(RED "Wrong commnand." NC " Try again.\n");
		}
	}

	free_list_queue(&list_q1);
	free_list_queue(&list_q2);

	return 0;
}

void pre_init_all(array_queue_t *array_q1, array_queue_t *array_q2,
				  list_queue_t *list_q1, list_queue_t *list_q2,
				  machine_t *a1, machine_t *a2, settings_t settings)
{
	free_list_queue(list_q1);
	free_list_queue(list_q2);

	memset(a1, 0, sizeof(*a1));
	memset(a2, 0, sizeof(*a2));

	memset(array_q1, 0, sizeof(*array_q1));
	memset(array_q2, 0, sizeof(*array_q2));

	memset(list_q1, 0, sizeof(*list_q1));
	memset(list_q2, 0, sizeof(*list_q2));

	INIT_ARRAY_QUEUE(array_q1);
	INIT_ARRAY_QUEUE(array_q2);

	INIT_LIST_QUEUE(list_q1);
	INIT_LIST_QUEUE(list_q2);

	a1->time_min = settings.time1_min;
	a1->time_max = settings.time1_max;

	a2->time_min = settings.time2_min;
	a2->time_max = settings.time2_max;

	array_q1->n_requests = MAX_QUEUE_SIZE;
	fill_list_queue(list_q1);
}

