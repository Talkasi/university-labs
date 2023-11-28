#include "stack.h"
#include "input.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

enum main_m {
	EXIT,
	ARR_STACK,
	LIST_STACK,
	EFFICIENCY,
	N_MAIN_C
};

enum arr_m {
	ARR_BACK = 1,
	ARR_ADD,
	ARR_DEL,
	ARR_PRINT,
	ARR_SORT,
	N_ARR_C
};

enum list_m {
	LIST_BACK = 1,
	LIST_ADD,
	LIST_DEL,
	LIST_PRINT,
	LIST_PRINT_FLOG,
	LIST_SORT,
	N_LIST_C
};

typedef unsigned long long	ull;

int	handle_arr_stack_ops();
int	handle_list_stack_ops();
void 	measure_eff();

int	main()
{
	int	rc;
	int	command = -1;
	while (command != EXIT) {
		printf("Command menu:   0 - Exit;\n"
		    "\t\t1 - Work with stack as array;\n"
		    "\t\t2 - Work with stack as list;\n"
		    "\t\t3 - Measure efficiency.\n");

		printf(">> Enter command: ");
		if (read_int(&command) != 0) {
			printf("Wrong command. It should be integer.\n");
			continue;
		}

		switch (command) {
		case EXIT:
			break;
		case ARR_STACK:
			rc = handle_arr_stack_ops();
			if (rc == EXIT)
				return 0;
			break;
		case LIST_STACK:
			rc = handle_list_stack_ops();
			if (rc == EXIT)
				return 0;
			break;
		case EFFICIENCY:
			measure_eff();
			break;
		default:
			printf("Wrong command. Try again.\n");
			break;
		}
	}

	return 0;
}


int	handle_arr_stack_ops()
{
	int	arr_c = -1;
	arr_stack_t s1;
	s1.ps = -1;

	arr_stack_t s2;
	s2.ps = -1;

	arr_stack_t res_s;
	res_s.ps = -1;

	while (arr_c != EXIT) {
		printf("Arr stack menu: 0 - Exit;\n"
		    "\t\t1 - Back to main menu (Warning! All data will be lost!);\n"
		    "\t\t2 - Add elems to stack;\n"
		    "\t\t3 - Del elem from stack;\n"
		    "\t\t4 - Print stack;\n"
		    "\t\t5 - Sort the first and the second stacks and store result in the third one.\n");

		printf(">> Enter command: ");
		if (read_int(&arr_c) != 0) {
			printf("Wrong command. It should be integer.\n");
			continue;
		}

		switch (arr_c) {
		case EXIT:
		case ARR_BACK:
			return arr_c;
		case ARR_ADD:
			 {
				int	el;
				int	stack_n;
				long	n_els;
				printf("Choose number of the stack you want to add element to.\n"
				    "1 - first one;\n"
				    "2 - second one.\n");

				printf(">> Enter stack number: ");
				while (read_int(&stack_n) != 0 || (stack_n != 1 && stack_n != 2))
					printf("Wrong stack number. Enter 1 or 2. Try again: ");

				printf(">> Enter number of elements to add (from 1 to %d): ", STACK_SIZE);
				while (read_long(&n_els) != 0 || n_els <= 0 || n_els > STACK_SIZE)
					printf("Wrong number of elements to add. Enter integer from 1 to %d: ", STACK_SIZE);

				for (long i = 0; i < n_els; ++i) {
					printf(">> Enter element to add: ");
					while (read_int(&el) != 0)
						printf("Wrong element. It should be integer. Try again: ");

					if (stack_n == 1)
						if (push_as(&s1, el))
							printf("Error. Stack is full.\n");

					if (stack_n == 2)
						if (push_as(&s2, el))
							printf("Error. Stack is full.\n");
				}

				break;
			}
		case ARR_DEL:
			 {
				int	el;
				int	stack_n;
				printf("Choose number of the stack you want to del element from.\n"
				    "1 - first one;\n"
				    "2 - second one.\n");

				printf(">> Enter stack number: ");
				while (read_int(&stack_n) != 0 || (stack_n != 1 && stack_n != 2))
					printf("Wrong stack number. Enter 1 or 2. Try again: ");


				if (stack_n == 1)
					if (pop_as(&s1, &el))
						printf("Error. Stack is empty.\n");

				if (stack_n == 2)
					if (pop_as(&s2, &el))
						printf("Error. Stack is empty.\n");

				break;
			}
		case ARR_PRINT:
			 {
				int	stack_n;
				printf("Choose number of the stack you want to print.\n"
				    "1 - first one;\n"
				    "2 - second one;\n"
				    "3 - stack with sort result\n");

				printf(">> Enter stack number: ");
				while (read_int(&stack_n) != 0 || (stack_n < 1 || stack_n > 3))
					printf("Wrong stack number. Enter 1, 2 or 3. Try again: ");

				if (stack_n == 1)
					print_as(&s1);
				else if (stack_n == 2)
					print_as(&s2);
				else
					print_as(&res_s);

				break;
			}
		case ARR_SORT:
		{
			arr_stack_t tmp1;
			tmp1.ps = -1;
			memcpy(&tmp1, &s1, sizeof(arr_stack_t));

			arr_stack_t tmp2;
			tmp2.ps = -1;
			memcpy(&tmp2, &s2, sizeof(arr_stack_t));

			sort_as(&s1);
			printf("Stack1 sorted:\n");
			print_as(&s1);

			sort_as(&s2);
			printf("Stack2 sorted:\n");
			print_as(&s2);

			res_s.ps = -1;

			if (merge_sorted_as(&s1, &s2, &res_s)) {
				printf("Too big stacks. Result stack will overflow. Can't merge stacks.\n");
				break;
			}

			printf("Result stack:\n");
			print_as(&res_s);

			memcpy(&s1, &tmp1, sizeof(arr_stack_t));
			memcpy(&s2, &tmp2, sizeof(arr_stack_t));

			break;
		}
		default:
			printf("Wrong command. Try again.\n");
			break;
		}
	}

	return 0;
}


int	handle_list_stack_ops()
{
	int	list_c = -1;
	list_stack_t s1;
	if (pre_init_ls(&s1)) {
		printf("Error while allocating memory.\n");
		return MALLOC_ERR;
	}

	list_stack_t s2;
	if (pre_init_ls(&s2)) {
		printf("Error while allocating memory.\n");
		return MALLOC_ERR;
	}

	list_stack_t res_s;
	if (pre_init_ls(&res_s)) {
		printf("Error while allocating memory.\n");
		return MALLOC_ERR;
	}

	while (list_c != EXIT) {
		printf("List stack menu: 0 - Exit;\n"
		    "\t\t 1 - Back to main menu (Warning! All data will be lost!);\n"
		    "\t\t 2 - Add elems to stack;\n"
		    "\t\t 3 - Del elem from stack;\n"
		    "\t\t 4 - Print stack;\n"
		    "\t\t 5 - Print free log of the stack;\n"
		    "\t\t 6 - Sort the first and the second stacks and store result in the third one.\n");

		printf(">> Enter command: ");
		if (read_int(&list_c) != 0) {
			printf("Wrong command. It should be integer.\n");
			continue;
		}

		switch (list_c) {
		case EXIT:
		case LIST_BACK:
			free_ls(&s1);
			free_ls(&s2);
			free_ls(&res_s);
			return list_c;
		case LIST_ADD:
			 {
				int	el;
				int	stack_n;
				long	n_els;
				printf("Choose number of the stack you want to add element to.\n"
				    "1 - first one;\n"
				    "2 - second one.\n");

				printf(">> Enter stack number: ");
				while (read_int(&stack_n) != 0 || (stack_n != 1 && stack_n != 2))
					printf("Wrong stack number. Enter 1 or 2. Try again: ");

				printf(">> Enter number of elements to add (from 1 to %d): ", STACK_SIZE);
				while (read_long(&n_els) != 0 || n_els <= 0 || n_els > STACK_SIZE)
					printf("Wrong number of elements to add. Enter integer from 1 to %d: ", STACK_SIZE);

				for (long i = 0; i < n_els; ++i) {
					printf(">> Enter element to add: ");
					while (read_int(&el) != 0)
						printf("Wrong element. It should be integer. Try again: ");

					if (stack_n == 1)
						if (push_ls(&s1, el))
							printf("Error. Stack is full.\n");

					if (stack_n == 2)
						if (push_ls(&s2, el))
							printf("Error. Stack is full.\n");
				}

				break;
			}
		case LIST_DEL:
			 {
				int	el;
				int	stack_n;
				printf("Choose number of the stack you want to del element from.\n"
				    "1 - first one;\n"
				    "2 - second one.\n");

				printf(">> Enter stack number: ");
				while (read_int(&stack_n) != 0 || (stack_n != 1 && stack_n != 2))
					printf("Wrong stack number. Enter 1 or 2. Try again: ");


				if (stack_n == 1)
					if (pop_ls(&s1, &el))
						printf("Error. Stack is empty.\n");

				if (stack_n == 2)
					if (pop_ls(&s2, &el))
						printf("Error. Stack is empty.\n");

				break;
			}
		case LIST_PRINT:
			 {
				int	stack_n;
				printf("Choose number of the stack you want to print.\n"
				    "1 - first one;\n"
				    "2 - second one;\n"
				    "3 - stack with sort result\n");

				printf(">> Enter stack number: ");
				while (read_int(&stack_n) != 0 || (stack_n < 1 || stack_n > 3))
					printf("Wrong stack number. Enter 1, 2 or 3. Try again: ");

				if (stack_n == 1)
					print_ls(&s1);
				else if (stack_n == 2)
					print_ls(&s2);
				else
					print_ls(&res_s);

				break;
			}
		case LIST_PRINT_FLOG:
			 {
				int	stack_n;
				printf("Choose number of the stack you want to print.\n"
				    "1 - first one;\n"
				    "2 - second one;\n"
				    "3 - stack with sort result\n");

				printf(">> Enter stack number: ");
				while (read_int(&stack_n) != 0 || (stack_n < 1 || stack_n > 3))
					printf("Wrong stack number. Enter 1, 2 or 3. Try again: ");

				if (stack_n == 1)
					print_freed_log(&s1);
				else if (stack_n == 2)
					print_freed_log(&s2);
				else
					print_freed_log(&res_s);

				break;
			}
		case LIST_SORT:
		{
			list_stack_t tmp1;
			if (pre_init_ls(&tmp1)) {
				printf("Error while allocating memory to save your stack for u.\n");
				break;
			}
			list_stack_t tmp2;
			if (pre_init_ls(&tmp2)) {
				printf("Error while allocating memory to save your stack for u.\n");
				break;
			}

			node_t *tmp_node = s1.head;
			while (tmp_node->next) {
				push_ls(&tmp1, tmp_node->el);
				tmp_node = tmp_node->next;
			}

			printf("Copied Stack1:\n");
			print_ls(&tmp1);

			tmp_node = s2.head;
			while (tmp_node->next) {
				push_ls(&tmp2, tmp_node->el);
				tmp_node = tmp_node->next;
			}

			printf("Copied Stack2:\n");
			print_ls(&tmp2);

			sort_ls(&s1);
			printf("Stack1 sorted: \n");
			print_ls(&s1);

			sort_ls(&s2);
			printf("Stack2 sorted:\n");
			print_ls(&s2);

			if (res_s.head->next != NULL) {
				free_ls(&res_s);
				if (pre_init_ls(&res_s)) {
					printf("Error while allocating memory.\n");
					return MALLOC_ERR;
				}
			}

			if (merge_sorted_ls(&s1, &s2, &res_s)) {
				printf("To big stacks. Result stack will overflow. Can't merge stacks.\n");
				break;
			}

			printf("Result stack:\n");
			print_ls(&res_s);

			tmp_node = tmp1.head;
			while (tmp_node->next) {
				push_ls(&s1, tmp_node->el);
				tmp_node = tmp_node->next;
			}

			tmp_node = tmp2.head;
			while (tmp_node->next) {
				push_ls(&s2, tmp_node->el);
				tmp_node = tmp_node->next;
			}

			free_ls(&tmp1);
			free_ls(&tmp2);
			break;
		}
		default:
			printf("Wrong command. Try again.\n");
			break;
		}
	}

	free_ls(&s1);
	free_ls(&s2);
	free_ls(&res_s);
	return 0;
}

ull     current_time()
{
	struct timespec ts;
	clockid_t clkid;
	clkid = CLOCK_REALTIME;
	clock_gettime(clkid, &ts);

	return ts.tv_sec * 1000000000 + ts.tv_nsec;
}


ull sum(ull *arr, long n)
{
	ull s = 0;

	for (long i = 0; i < n; ++i)
		s += arr[i];

	return s;
}


#define N_TESTS_M 50
#define N_TESTS_RES 10
#define MAX_N_ELEMS 1000
#define STEP MAX_N_ELEMS / N_TESTS_RES
void print_eff(ull *avg_arr, ull *avg_list, size_t *mem_arr, size_t *mem_list)
{
	printf("┌─────────────────┬───────────────────┬────────────────────┬─────────────────┬────────────────┐\n"
	    "│ Number of elems │ Time of arr stack │ Time of list stack │ Array stack mem │ List stack mem │\n"
	    "├─────────────────┼───────────────────┼────────────────────┼─────────────────┼────────────────┤\n");
	size_t j = 0;
	for (int i = 1; i < MAX_N_ELEMS; i += STEP, ++j)
		printf("│ %15d │ %14lld us │ %15lld us │ %13ld b │ %12ld b │\n", i, avg_arr[j], avg_list[j], mem_arr[j], mem_list[j]);
	printf("└─────────────────┴───────────────────┴────────────────────┴─────────────────┴────────────────┘\n");

}


size_t sizeof_arr(arr_stack_t *st)
{
	size_t s = sizeof(int) * STACK_SIZE;
	return s;
}


size_t sizeof_list(list_stack_t *st)
{
	size_t s = sizeof(node_t) * st->n_els;
	return s;
}


void measure_eff()
{
	list_stack_t list_s1;
	if (pre_init_ls(&list_s1)) {
		printf("Error while allocating memory.\n");
		return;
	}

	list_stack_t list_s2;
	if (pre_init_ls(&list_s2)) {
		printf("Error while allocating memory.\n");
		return;
	}

	list_stack_t list_s_res;
	if (pre_init_ls(&list_s_res)) {
		printf("Error while allocating memory.\n");
		return;
	}

	arr_stack_t arr_s1;
	arr_s1.ps = -1;
	arr_stack_t arr_s2;
	arr_s2.ps = -1;
	arr_stack_t arr_s_res;
	arr_s_res.ps = -1;

	ull     time_list[N_TESTS_M];
	ull     time_arr[N_TESTS_M];

	ull 	avg_list[N_TESTS_RES];
	ull 	avg_arr[N_TESTS_RES];

	size_t mem_list[N_TESTS_RES];
	size_t mem_arr[N_TESTS_RES];

	size_t i = 0;
	for (int n_els = 1; n_els < MAX_N_ELEMS; n_els += STEP, ++i) {
		g_rand_as(&arr_s1, n_els);
		g_rand_as(&arr_s2, n_els);
		arr_s_res.ps = -1;
		//printf("%zu %zu\n", sizeof_arr(&arr_s1), sizeof_arr(&arr_s2));
		mem_arr[i] = sizeof_arr(&arr_s1) + sizeof_arr(&arr_s2);

		for (int test = 0; test < N_TESTS_M; ++test) {
			time_arr[test] = current_time();
			sort_as(&arr_s1);
			sort_as(&arr_s2);
			merge_sorted_as(&arr_s1, &arr_s2, &arr_s_res);
			time_arr[test] = current_time() - time_arr[test];
		}
		avg_arr[i] = sum(time_arr, N_TESTS_M) / N_TESTS_M;

		free_ls(&list_s1);
		pre_init_ls(&list_s1);
		g_rand_ls(&list_s1, n_els);

		free_ls(&list_s2);
		pre_init_ls(&list_s2);
		g_rand_ls(&list_s2, n_els);

		free_ls(&list_s_res);
		pre_init_ls(&list_s_res);
		//printf("%zu %zu\n", sizeof_list(&list_s1), sizeof_list(&list_s2));
		mem_list[i] = sizeof_list(&list_s1) + sizeof_list(&list_s2);

		for (int test = 0; test < N_TESTS_M; ++test) {
			time_list[test] = current_time();
			sort_ls(&list_s1);
			sort_ls(&list_s2);
			merge_sorted_ls(&list_s1, &list_s2, &list_s_res);
			time_list[test] = current_time() - time_list[test];
		}
		avg_list[i] = sum(time_list, N_TESTS_M) / N_TESTS_M;

		//printf("%zu %zu %zu\n", sizeof_list(&list_s1), sizeof_list(&list_s2), sizeof_list(&list_s_res));
		//printf("%zu %zu %zu\n", sizeof_arr(&arr_s1), sizeof_arr(&arr_s2), sizeof_arr(&arr_s_res));
		//printf("-------\n");
		mem_list[i] += sizeof_list(&list_s_res);
		mem_arr[i] += sizeof_arr(&arr_s_res);
	}

	print_eff(avg_arr, avg_list, mem_arr, mem_list);
	free_ls(&list_s1);
	free_ls(&list_s2);
	free_ls(&list_s_res);
}


// main.c:445