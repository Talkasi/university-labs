#include "bin_tree.h"
#include "hash_table.h"
#include "input.h"
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <sys/time.h>
#include <string.h>

void print_menu(char *m[], int n_c);
unsigned long long current_time();

typedef enum {
	EXIT,
	ADD,
	DELETE,
	INIT,
	DELETE_SPEC,
	PRINT,
	MEASURE_EFF,
	N_COMMANDS
} commands;

#define N_TESTS 50
#define TEST_C 'a'
#define TEST_FILE "tests/test"
#define TEST_FILE_CP "tests/tmp"

int	main()
{
	node_t *bin_search_tree = NULL;
	node_t *avl_tree = NULL;
	list_hash_table_t *list_hash_table = create_list_hash_table();
	arr_hash_table_t *arr_hash_table = create_arr_hash_table();

	FILE *f = fopen(TEST_FILE, "r+");
	if (!f)
		return 0;

	char	*menu[] = {
		"0 - Exit",
		"1 - Insert",
		"2 - Delete",
		"3 - Init",
		"4 - Delete all data starting from the particular letter",
		"5 - Print",
		"6 - Measure efficiency",
	};

	int	command = -1;
	while (command != EXIT) {
		printf("Command menu:\n");
		print_menu(menu, N_COMMANDS);

		printf("> Enter command: ");
		if (read_int(&command) || command < 0) {
			printf("Wrong number. Please, try again.\n");
			continue;
		}

		switch (command) {
		case EXIT:
			break;
		case ADD:
		{
			char word[MAX_WORD_LEN];
			printf("Enter data to add: ");
			while (read_str(stdin, word, MAX_WORD_LEN) == 0)
				printf("Wrong word. Try again.\n");

			node_t *new_node;
			if (create_node(&new_node, word)) {
				printf("Error while allocating data\n");
				break;
			}

			bin_search_tree = put_data(bin_search_tree, new_node);
			avl_tree = insert_balanced(avl_tree, word);

			insert_list_hash_table(list_hash_table, word);
			insert_arr_hash_table(arr_hash_table, word);

			break;
		}
		case DELETE:
		{
			char word[MAX_WORD_LEN];
			if (bin_search_tree == NULL || avl_tree == NULL) {
				printf("No data\n");
				break;
			}

			printf("Enter data to delete: ");
			while (read_str(stdin, word, MAX_WORD_LEN) == 0)
				printf("Wrong word. Try again.\n");

			avl_tree = delete_data(avl_tree, word);
			bin_search_tree = delete_data(bin_search_tree, word);

			delete_list_hash_table(list_hash_table, word);
			delete_arr_hash_table(arr_hash_table, word);

			break;
		}
		case INIT:
			free_tree(&avl_tree);
			free_tree(&bin_search_tree);
			destroy_list_hash_table(&list_hash_table);
			destroy_arr_hash_table(&arr_hash_table);
			list_hash_table = create_list_hash_table();
			arr_hash_table = create_arr_hash_table();

			create_tree_from_file(f, &bin_search_tree);
			create_balanced_from_bin_search_tree(&avl_tree, bin_search_tree);
			create_list_hash_table_from_file(f, list_hash_table);
			create_arr_hash_table_from_file(f, arr_hash_table);
			break;
		case DELETE_SPEC:
			if (bin_search_tree == NULL || avl_tree == NULL) {
				printf("No data\n");
				break;
			}

			printf("> Enter letter to delete by: ");
			char c;
			while (read_char(&c) || c == EOF)
				printf("Wrong input try again: ");

			bin_search_tree = delete_by_first_letter_tree(bin_search_tree, c);
			avl_tree = delete_by_first_letter_tree(avl_tree, c);
			break;
		case PRINT:
			if (avl_tree == NULL || bin_search_tree == NULL) {
				printf("No data\n");
				break;
			}

			if (avl_tree->left == NULL && avl_tree->right == NULL) {
				printf("AVL avl_tree does not have any leaves\n");
				printf("AVL tree root: %s\n\n", avl_tree->data);
			} else if (open_tree_img("avl_tree", avl_tree))
				printf("Error while printing the tree.\n\n");


			if (bin_search_tree->left == NULL && bin_search_tree->right == NULL) {
				printf("Bin Search Tree does not have any leaves\n");
				printf("Bin Search Tree root: %s\n\n", bin_search_tree->data);
			} else if (open_tree_img("bin_search_tree", bin_search_tree))
				printf("Error while printing the tree.\n\n");

			printf("List hash table:\n");
			print_list_hash_table(list_hash_table);

			printf("Array hash table:\n");
			print_arr_hash_table(arr_hash_table);
			
			break;
		case MEASURE_EFF:
		{
			free_tree(&avl_tree);
			free_tree(&bin_search_tree);
			destroy_list_hash_table(&list_hash_table);
			destroy_arr_hash_table(&arr_hash_table);
			list_hash_table = create_list_hash_table();
			arr_hash_table = create_arr_hash_table();

			create_tree_from_file(f, &bin_search_tree);
			create_balanced_from_bin_search_tree(&avl_tree, bin_search_tree);
			create_list_hash_table_from_file(f, list_hash_table);
			create_arr_hash_table_from_file(f, arr_hash_table);


			printf(">> SEARCH EFFICIENCY\n");
			printf("> Bin Search Tree\n");
			size_t size = 0;
			size_t n_compares = 0;
			unsigned long long time;
			unsigned long long all_time = 0;
			for (int i = 0; i < N_TESTS; ++i) {
				time = current_time();
				search_bin_tree(bin_search_tree, "word", &n_compares);
				all_time += current_time() - time;
			}
			printf("Average search time: %lld\n", all_time / N_TESTS);
			printf("Avarage number of compares: %zu\n", n_compares / N_TESTS);
			calc_size_apply(bin_search_tree, calc_node_size, &size);
			printf("Size: %zu\n\n", size);

			printf("> AVL Tree\n");
			size = 0;
			all_time = 0;
			n_compares = 0;
			for (int i = 0; i < N_TESTS; ++i) {
				time = current_time();
				search_bin_tree(avl_tree, "word", &n_compares);
				all_time += current_time() - time;
			}
			printf("Average search time: %lld\n", all_time / N_TESTS);
			printf("Avarage number of compares: %zu\n", n_compares / N_TESTS);
			calc_size_apply(avl_tree, calc_node_size, &size);
			printf("Size: %zu\n\n", size);

			int max_n_compares;
			printf("Enter number of compares allowed before the tables restruct: ");
			while (read_int(&max_n_compares) || max_n_compares < 0) {
				printf("Wrong number. Please, try again.\n");
				continue;
			}

			printf("> Hash table based on list array\n");
			for (int j = 0; j < 2; ++j) {
				all_time = 0;
				for (int i = 0; i < N_TESTS; ++i) {
					time = current_time();
					search_list_hash_table(list_hash_table, "word");
					all_time += current_time() - time;
				}
				printf("Average search time: %lld\n", all_time / N_TESTS);
				printf("Avarage number of compares: %lld\n", 
						list_hash_table->n_compare / list_hash_table->n_searches);
				printf("Size: %zu\n\n", sizeof(list_hash_table_t));

				if (j == 0 && list_hash_table->n_compare / list_hash_table->n_searches > max_n_compares) {
					restruct_list_hash_table(list_hash_table);
					printf("> Hash table based on list array was restructed\n");
				} else
					break;
			}

			printf("> Hash table based on data array\n");
			for (int j = 0; j < 2; ++j) {
				all_time = 0;
				for (int i = 0; i < N_TESTS; ++i) {
					time = current_time();
					search_arr_hash_table(arr_hash_table, "word");
					all_time += current_time() - time;
				}
				printf("Average search time: %lld\n", all_time / N_TESTS);
				printf("Avarage number of compares: %lld\n", 
						arr_hash_table->n_compare / arr_hash_table->n_searches);
				printf("Size: %zu\n\n", sizeof(arr_hash_table_t));


				if (j == 0 && arr_hash_table->n_compare / arr_hash_table->n_searches > max_n_compares) {
					restruct_arr_hash_table(arr_hash_table);
					printf("> Hash table based on data array was restructed\n");
				} else
					break;
			}

			break;
		}
		default:
			printf("Wrong command. It must be an integer from 0 to %d."
			    "Try again.\n", N_COMMANDS);
			break;
		}
	}

	free_tree(&avl_tree);
	free_tree(&bin_search_tree);
	destroy_list_hash_table(&list_hash_table);
	destroy_arr_hash_table(&arr_hash_table);
	fclose(f);
}

unsigned long long current_time()
{
	struct timespec ts = {};
	clockid_t clkid;
	clkid = CLOCK_REALTIME;
	clock_gettime(clkid, &ts);

	return ts.tv_sec * 1000000000 + ts.tv_nsec;
}

void print_menu(char *m[], int n_c)
{
	for (int i = 0; i < n_c; ++i)
		printf("\t\t%s\n", m[i]);
}
