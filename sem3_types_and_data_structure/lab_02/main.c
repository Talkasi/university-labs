#include <stdio.h>
#include <string.h>
#include "db.h"

#define ERR_OPEN_DB 1
#define MAX_NAME_LEN 100
#define ERR -1;
void pinfo();
void pmenu();
int read_line(FILE *f, char *s, int bound);
unsigned long long avg(unsigned long long arr[], int len);

enum {
	MENU,
	OPEN,
	PRINT,
	ADD,
	DELETE,
	SEARCH,
	SORT_KEY,
	SORT_ORIGIN,
	PRINT_BY_KEY,
	EFFICIENCY,
	SAVE,
	EXIT,
	N_COMMANDS
} command_list;
#define MEASURE_N 1000

int main(int argc, char *argv[]) {
	pinfo();
	pmenu();

	flat_t flats[MAX_NRECORDS];
	fkey_t keys[MAX_NRECORDS];

	int n_flats = 0;
	int command = -1;

	FILE *db;
	int db_is_opened = 0;
	char db_name[MAX_NAME_LEN];

	long tmp;
	char sort;
	while (command != EXIT) {
		printf(">> Enter number of the command to execute: ");
		if (read_long(&tmp, N_COMMANDS) < 0)
			command = -1;
		else
			command = (int) tmp;

		switch (command) {
			case MENU:
				pmenu();
				break;
			case OPEN:
				if (db_is_opened) {
					printf("Warning: you were working with %s database. If you haven't save changes "
						  "they will be lost.\n", db_name);
					printf("Are you sure you want to continue? [Y/n]: ");
					char prompt;
					if (read_char(&prompt) < 0 || (prompt != '\n' && prompt != 'y' && prompt != 'Y')) {
						printf("Confirmation failed.\n"
							  "If you wanted to confirm opening db, you should execute this command "
							  "again and hit enter or type `y` or `Y` to proceed.\n");
						break;
					}
				}

				while (1) {
					printf("Enter name of the database: ");
					if (read_line(stdin, db_name, MAX_NAME_LEN) < 0) {
						printf("Error occured while reading database name. Please, try again.\n");
						continue;
					}

					db = fopen(db_name, "r+");
					if (db == NULL) {
						printf("Error while opening the database. Please, try again with another one.\n");
						continue;
					}

					int rc;
					if ((rc = read_db(db, flats, keys, &n_flats)) != 0) {
						printf("%s is not a valid database. Please, try again with a correct one.\n", db_name);
						fclose(db);
						continue;
					} else {
						fclose(db);
						db_is_opened = 1;
						break;
					}
				}

				break;
			case PRINT:
				if (db_is_opened == 0)
					printf("Error occured. Database is not opened.\n");
				else if (n_flats > 0)
					print_db(flats, n_flats);
				else
					printf("Error occured. Database is empty.\n");

				break;
			case ADD:
				if (db_is_opened == 0) {
					printf("Error occured. Database is not opened.\n");
					break;
				}

				if (n_flats + 1 > MAX_NRECORDS) {
					printf("Error occured. Database is full.\n");
					break;
				}

				flat_t new_record;
				read_flat(&new_record);

				add_record(flats, &n_flats, &new_record);
				for (int i = 0; i < n_flats; ++i) {
					keys[i].n = i + 1;
					keys[i].cost = flats[i].cost_per_square;
				}

				break;
			case DELETE:
				if (db_is_opened == 0) {
					printf("Error occured. Database is not opened.\n");
					break;
				}

				if (n_flats == 0) {
					printf("Nothing to delete. Database is empty.\n");
					break;
				}

				int del_n;
				while (1) {
					printf("Enter number of record to delete in boundaries [1, %d]: ", n_flats);
					if (read_long(&tmp, n_flats) < 0 || tmp <= 0)
						printf("Wrong record number. Please, try again.\n");
					else {
						del_n = (int) tmp;
						break;
					}
				}

				del_record(flats, &n_flats, del_n - 1);
				for (int i = 0; i < n_flats; ++i) {
					keys[i].n = i + 1;
					keys[i].cost = flats[i].cost_per_square;
				}

				break;
			case SEARCH:
				if (db_is_opened == 0) {
					printf("Error occured. Database is not opened.\n");
					break;
				}

				if (n_flats == 0) {
					printf("Error occured. Database is empty.\n");
					break;
				}

				long min, max;
				while (1) {
					printf("Enter min boundary of the cost per square in boundaries [1, %d]: ", MAX_COST - 1);
					if (read_long(&min, MAX_COST - 1) < 0 || min <= 0) {
						printf("Wrong boundary. Try again.\n");
						continue;
					}

					while (1) {
						printf("Enter max boundary of the cost per square in "
						 	  "boundaries [%ld, %d]: ", min + 1, MAX_COST);
						if (read_long(&max, MAX_COST) < 0 || max <= 0)
							printf("Wrong boundary. Try again.\n");
						else
							break;
					}

					if (min >= max)
						printf("Min should be less than max. Try again.\n");
					else if (max > MAX_COST)
						printf("Boundaries should be less than %d.Try again.\n", MAX_COST);
					else
						break;
				}

				print_special(flats, n_flats, min, max);
				break;
			case SORT_KEY:
				if (db_is_opened == 0) {
					printf("Error occured. Database is not opened.\n");
					break;
				}

				if (n_flats == 0) {
					printf("Nothing to sort. Database is empty.\n");
					break;
				}

				printf("Key table before sorting:\n");
				print_keys(keys, n_flats);

				while (1) {
					printf("Chose sorting. 1 for buble sort, 2 for insertion sort: ");
					if (read_char(&sort)  < 0 || (sort != '1' && sort != '2'))
						printf("Wrong input. Please, try again.\n");
					else
						break;
				}

				if (sort == '1')
					buble_sort_k(keys, n_flats);
				else
					insertion_sort_k(keys, n_flats);

				printf("Key table, sorted by cost per square:\n");
				print_keys(keys, n_flats);
				break;
			case SORT_ORIGIN:
				if (db_is_opened == 0) {
					printf("Error occured. Database is not opened.\n");
					break;
				}

				if (n_flats == 0) {
					printf("Nothing to sort. Database is empty.\n");
					break;
				}

				while (1) {
					printf("Chose sorting. 1 for buble sort, 2 for insertion sort: ");
					if (read_char(&sort)  < 0 || (sort != '1' && sort != '2'))
						printf("Wrong input. Please, try again.\n");
					else
						break;
				}

				if (sort == '1')
					buble_sort_f(flats, n_flats);
				else
					insertion_sort_f(flats, n_flats);

				for (int i = 0; i < n_flats; ++i) {
					keys[i].n = i + 1;
					keys[i].cost = flats[i].cost_per_square;
				}

				printf("Database, sorted by cost per square:\n");
				print_db(flats, n_flats);
				break;
			case PRINT_BY_KEY:
				if (db_is_opened == 0) {
					printf("Error occured. Database is not opened.\n");
					break;
				}

				if (n_flats == 0) {
					printf("Nothing to print. Database is empty.\n");
					break;
				}

				print_flats_by_key(flats, keys, n_flats);
				break;
			case EFFICIENCY:
				if (db_is_opened == 0) {
					printf("Error occured. Database is not opened.\n");
					break;
				}

				if (n_flats == 0) {
					printf("Nothing to measure. Database is empty.\n");
					break;
				}

				fkey_t tmp_keys[MAX_NRECORDS];
				unsigned long long t_keys_buble[MEASURE_N];
				unsigned long long t1, t2;
				for (int i = 0; i < MEASURE_N; ++i) {
					memcpy(tmp_keys, keys, n_flats * sizeof(fkey_t));
					t1= current_time();
					buble_sort_k(tmp_keys, n_flats);
					t2 = current_time();
					t_keys_buble[i] = t2 - t1;
				}
				unsigned long long avg_keys_buble = avg(t_keys_buble, n_flats);


				unsigned long long t_keys_insertion[MAX_NRECORDS];
				for (int i = 0; i < MEASURE_N; ++i) {
					memcpy(tmp_keys, keys, n_flats * sizeof(fkey_t));
					t1 = current_time();
					insertion_sort_k(tmp_keys, n_flats);
					t2 = current_time();
					t_keys_insertion[i] = t2 - t1;
				}
				unsigned long long avg_keys_insertion = avg(t_keys_insertion, n_flats);

				flat_t tmp_flats[MAX_NRECORDS];
				unsigned long long t_flats_buble[MEASURE_N];
				for (int i = 0; i < MEASURE_N; ++i) {
					memcpy(tmp_flats, keys, n_flats * sizeof(flat_t));
					t1 = current_time();
					buble_sort_f(tmp_flats, n_flats);
					t2 = current_time();
					t_flats_buble[i] = t2 - t1;
				}
				unsigned long long avg_flats_buble = avg(t_flats_buble, n_flats);

				unsigned long long t_flats_insertion[MAX_NRECORDS];
				for (int i = 0; i < MEASURE_N; ++i) {
					memcpy(tmp_flats, keys, n_flats * sizeof(flat_t));
					t1 = current_time();
					insertion_sort_f(tmp_flats, n_flats);
					t2 = current_time();
					t_flats_insertion[i] = t2 - t1;
				}
				unsigned long long avg_flats_insertion = avg(t_flats_insertion, n_flats);

				print_t_efficiency(avg_keys_buble, avg_keys_insertion,
						 	     avg_flats_buble, avg_flats_insertion);
				print_m_efficiency(sizeof(fkey_t) * n_flats, sizeof(fkey_t) * n_flats,
						 	     sizeof(flat_t) * n_flats, sizeof(flat_t) * n_flats);
				printf("Bubble sort efficiency\n");
				print_p_efficiency(avg_keys_buble, avg_flats_buble);
				printf("Insertion efficiency\n");
				print_p_efficiency(avg_keys_insertion, avg_flats_insertion);
				break;
			case SAVE:
				if (db_is_opened == 0) {
					printf("Error occured. Nothing to save.\n");
					break;
				}

				db = fopen(db_name, "w");
				save_db(db, flats, n_flats);
				fclose(db);
				break;
			case EXIT:
				if (db_is_opened) {
					printf("Warning: you were working with %s database. "
						  "If you haven't save changes they will be lost.\n", db_name);
					printf("Are you sure you want to continue? [Y/n]:  ");
					char prompt;
					if (read_char(&prompt) < 0 || (prompt != '\n' && prompt != 'y' && prompt != 'Y')) {
						printf("Confirmation failed.\n"
							  "If you wanted to exit, you should execute this "
							  "command again and hit enter or type `y` or `Y`.\n");
						command = -1;
						break;
					}
				}
				break;
			default:
				printf("Wrong command. Please, try again.\n");
				break;
		}
	}

	return 0;
}

void pinfo() {
	printf("This is the program which helps you to work with simple text databases.\n");
	printf("Valid command is an integer from 0 to 11.\n");
}

void pmenu() {
	printf("> Command Menu: 0 - menu\n"
		  "\t\t1 - open database\n"
		  "\t\t2 - print database\n"
		  "\t\t3 - add record to the end of the database\n"
		  "\t\t4 - delete record by its number\n"
		  "\t\t5 - find each secondary housing with 2 rooms and no animals with given cost boundaries\n"
		  "\t\t6 - sort and print key table\n"
		  "\t\t7 - sort and print original database\n"
		  "\t\t8 - print original database by key table\n"
		  "\t\t9 - measure efficiency\n"
		  "\t\t10 - save database\n"
		  "\t\t11 - exit program\n");
}

unsigned long long avg(unsigned long long arr[], int len) {
	unsigned long long sum = 0;
	for (int i = 0; i < len; ++i)
		sum += arr[i];

	return sum / len;
}