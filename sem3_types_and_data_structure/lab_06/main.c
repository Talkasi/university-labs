#include "bin_tree.h"
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
#define TEST_FILE "test"
#define TEST_FILE_CP "test_cp"

int	main()
{
	node_t *root;
	FILE *f = fopen(TEST_FILE, "r+");
	if (!f)
		return 0;

	char	*menu[] = {
		"0 - Exit",
		"1 - Add element to the binary search tree",
		"2 - Delete element from the binary search tree",
		"3 - Init binary search tree from file",
		"4 - Delete all data starting from the particular letter from a binary search tree",
		"5 - Print binary search tree",
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

			root = put_data(root, new_node);
			break;
		}
		case DELETE:
		{
			char word[MAX_WORD_LEN];
			if (root == NULL) {
				printf("Tree is empty\n");
				break;
			}

			printf("Enter data to delete: ");
			while (read_str(stdin, word, MAX_WORD_LEN) == 0)
				printf("Wrong word. Try again.\n");

			root = delete_data(root, word);
			break;
		}
		case INIT:
			if (create_tree_from_file(f, &root))
				printf("Error while reading from file.\n");

			break;
		case DELETE_SPEC:
			if (root == NULL) {
				printf("Tree is empty\n");
				break;
			}

			printf("> Enter letter to delete by: ");
			char c;
			while (read_char(&c) || c == EOF)
				printf("Wrong input try again: ");

			root = delete_by_first_letter_tree(root, c);
			break;
		case PRINT:
			if (root == NULL) {
				printf("Tree is empty\n");
				break;
			}

			if (root->left == NULL && root->right == NULL) {
				printf("Tree does not have any leaves\n");
				printf("Tree root: %s\n", root->data);
				break;
			}

			if (open_tree_img("test", root))
				printf("Error while printing the tree.\n");

			break;
		case MEASURE_EFF:
		{
			unsigned long long time;
			unsigned long long all_time = 0;
			for (int i = 0; i < N_TESTS; ++i) {
				copyFile(TEST_FILE, TEST_FILE_CP);
				time = current_time();
				delete_by_first_letter_file(TEST_FILE_CP, TEST_C);
				all_time += current_time() - time;
			}
			printf("Average delete time in the file: %lld\n", all_time / N_TESTS);

			all_time = 0;
			for (int i = 0; i < N_TESTS; ++i) {
				create_tree_from_file(f, &root);
				time = current_time();
				delete_by_first_letter_tree(root, TEST_C);
				all_time += current_time() - time;
			}
			printf("Average delete time in the binary search tree: %lld\n", all_time / N_TESTS);

			break;
		}
		default:
			printf("Wrong command. It must be an integer from 0 to %d."
			    "Try again.\n", N_COMMANDS);
			break;
		}
	}

	free_tree(&root);
	fclose(f);
}

// int main() {

// 	node_t *root;

// 	create_tree_from_file(f, &root, words, &n_words);
// 	open_tree_img("test", root);
// 	delete_by_first_letter(root, 'd');
// 	open_tree_img("test", root);

// 	free_tree(root);
// 	fclose(f);
// 	return 0;
// }
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
