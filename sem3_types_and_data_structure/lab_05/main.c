#include "queue.h"
#include <stdio.h>
#include <string.h>

#define DEFAULT_QUEUE_1_MIN_TIME 0
#define DEFAULT_QUEUE_1_MAX_TIME 6

#define DEFAULT_QUEUE_2_MIN_TIME 1
#define DEFAULT_QUEUE_2_MAX_TIME 8

#define DEFAULT_POSSIBILITY 0.7

#define SWITCHER ARRAY

enum commands {
	EXIT,
	CHANGE_QUEUE1_TIME,
	CHANGE_QUEUE2_TIME,
	CHANGE_POSSIBILITY,
	PROCESS_ARR_VAR,
	PROCESS_LIST_VAR
};

int	main(void)
{
	machine_t a1;
	machine_t a2;

	memset(&a1, 0, sizeof(a1));
	memset(&a2, 0, sizeof(a2));

	a1.time_min = DEFAULT_QUEUE_1_MIN_TIME;
	a1.time_max = DEFAULT_QUEUE_1_MAX_TIME;

	a2.time_min = DEFAULT_QUEUE_2_MIN_TIME;
	a2.time_max = DEFAULT_QUEUE_2_MAX_TIME;

	double possibility = DEFAULT_POSSIBILITY;

	array_queue_t array_q1 = {};
	array_queue_t array_q2 = {};

	list_queue_t list_q1 = {};
	list_queue_t list_q2 = {};

	array_q1.n_requests = MAX_QUEUE_SIZE;
	fill_list_queue(&list_q1);

	int command;
	while (command != EXIT) {
		if (read_int(&command) || command < 0) {
			printf("Wrong number. Please, try again.\n");
			continue;
		}

		switch (command) {
		case EXIT:
			break;
		case CHANGE_QUEUE1_TIME:
			printf("Enter minimum time border of the first queue (integer): ");
			while (read_int(&a1.time_min) || a1.time_min < 0)
				printf("Wrong time border. Try again: ");
			
			printf("Enter maximum time border of the first queue (integer): ");
			while (read_int(&a1.time_max) || a1.time_max < 0)
				printf("Wrong time border. Try again: ");
			break;
		case CHANGE_QUEUE2_TIME:
			printf("Enter minimum time border of the secind queue (integer): ");
			while (read_int(&a2.time_min) || a2.time_min < 0)
				printf("Wrong time border. Try again: ");
			
			printf("Enter maximum time border of the secind queue (integer): ");
			while (read_int(&a2.time_max) || a2.time_max < 0)
				printf("Wrong time border. Try again: ");
			break;
		case CHANGE_POSSIBILITY:
			printf("Enter possibility for the request to enter the secind queue in [0, 1]: ");
			while (read_double(&possibility) || possibility < 0 || possibility > 1)
				printf("Wrong possibility. It must be number from 0 to 1. Try again: ");
			break;
		case PROCESS_ARR_VAR:
			array_process(&array_q1, &array_q2, &a1, &a2);
			break;
		case PROCESS_LIST_VAR:
			list_process(&list_q1, &list_q2, &a1, &a2);
			break;
		default:
			printf("Wrong commnand. Try again.\n");
		}
	}

	free_list_queue(&list_q1);
	free_list_queue(&list_q2);

	return 0;
}

