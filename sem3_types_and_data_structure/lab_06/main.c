#include "bin_tree.h"
#include "input.h"
#include <string.h>

void print_menu(char *m[], int n_c);

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

int	main()
{
	char words[MAX_N_WORDS][MAX_WORD_LEN] = {};
	size_t n_words;
	node_t *root;
	FILE *f = fopen("test", "r+");
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
			while (fread_line(stdin, word, MAX_WORD_LEN) == 0)
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
			if (root == NULL) {
				printf("Tree is empty\n");
				break;
			}

			char word[MAX_WORD_LEN];
			printf("Enter data to delete: ");
			while (fread_line(stdin, word, MAX_WORD_LEN) == 0)
				printf("Wrong word. Try again.\n");

			root = delete_data(root, word);
			break;
		}
		case INIT:
			free_tree(root);
			if (create_tree_from_file(f, &root, words, &n_words))
				printf("Error while reading from file.\n");

			break;
		case DELETE_SPEC:
			if (root == NULL) {
				printf("Tree is empty\n");
				break;
			}

			printf("> Enter letter to delete by: ");
			char c;
			read_char(&c);
			while (c == EOF)
				printf("Wrong input try again: ");

			root = delete_by_first_letter_tree(root, c);
			break;
		case PRINT:
			if (root == NULL) {
				printf("Tree is empty\n");
				break;
			}

			if (open_tree_img("test", root))
				printf("Error while printing the tree.\n");

			break;
		case MEASURE_EFF:
			
			break;
		default:
			printf("Wrong command. It must be an integer from 0 to %d."
			    "Try again.\n", N_COMMANDS);
			break;
		}
	}

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

void print_menu(char *m[], int n_c)
{
	for (int i = 0; i < n_c; ++i)
		printf("\t\t%s\n", m[i]);
}
