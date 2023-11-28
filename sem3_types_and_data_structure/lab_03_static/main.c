#include "input.h"
#include "matrix.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>

enum main_m {
	EXIT,
	INPUT_DATA,
	EFFICIENCY,
	PRINT_DATA,
	MUL_DATA,
	N_MENU_C
};

enum print_m {
	MBC1 = 1,
	MBR2,
	MBR_RES,
	MTX1,
	MTX2,
	MTX_RES,
	N_PRINT_C
};

enum mul_m {
	MB = 1,
	MTX,
	BOTH,
	N_MUL_C
};

enum input_m {
	INPUT_FROM_FILE  = 1,
	INPUT_FROM_KEYBOARD,
	N_INPUT_C
};

#define FILE_OPEN_ERR 101
#define MATRIX_TYPE_ERR 102

typedef unsigned long long	ull;

void print_menu(char *m[], int n_c);
void pre_init_all(mbc *mbc1, mbr *mbr2, mbr *mbr_res, mtx *mtx1, mtx *mtx2, mtx *mtx_res);
void measure_eff(mbc *mbc1, mbr *mbr2, mbr *mbr_res, mtx *mtx1, mtx *mtx2, mtx *mtx_res);
int	scan_command(char *menu, char *command_name, int min, int max);
int	input_matrixes(mbc *mbc1, mbr *mbr2, mtx *mtx1, mtx *mtx2);
void generate_all(mbc *mbc1, mbr *mbr2, mtx *mtx1, mtx *mtx2, int persent);

int	main()
{
	char	*menu[] = {
		"0 - Exit",
		"1 - Input matrixes",
		"2 - Measure efficiency",
		"3 - Print matrixes",
		"4 - Multiply matrixes",
	};

	mbc mbc1;
	mbr mbr2;
	mbr mbr_res;

	mtx mtx1;
	mtx mtx2;
	mtx mtx_res;

	pre_init_all(&mbc1, &mbr2, &mbr_res, &mtx1, &mtx2, &mtx_res);

	int	command = -1;
	int curr_n_commands = 3;
	while (command != EXIT) {
		printf("Command menu:\n");
		print_menu(menu, curr_n_commands);

		command = scan_command("", "main", 0, curr_n_commands - 1);

		switch (command) {
		case EXIT:
			break;
		case INPUT_DATA:
			input_matrixes(&mbc1, &mbr2, &mtx1, &mtx2);
			curr_n_commands = N_MENU_C;
			break;
		case PRINT_DATA:
			 {
				int	print_c = scan_command(
				    "Print menu:\n\t\t1 - mtx by column (the first multiplyer)\n"
				    "\t\t2 - mtx by row (the second multiplyer)\n"
				    "\t\t3 - mtx by row (mul result)\n"
				    "\t\t4 - ordinary mtx (the first multiplyer)\n"
				    "\t\t5 - ordinary mtx (the second multiplyer)\n"
				    "\t\t6 - ordinary mtx (mul result)\n",
				    "print", 1, N_PRINT_C -1);

				switch (print_c) {
				case MBC1:
					print_mbc(&mbc1);
					break;
				case MBR2:
					print_mbr(&mbr2);
					break;
				case MBR_RES:
					print_mbr(&mbr_res);
					break;
				case MTX1:
					print_mtx(&mtx1);
					break;
				case MTX2:
					print_mtx(&mtx2);
					break;
				case MTX_RES:
					print_mtx(&mtx_res);
					break;
				default:
					break;
				}
				break;
			}
		case MUL_DATA:
			 {
				int	mul_c = scan_command("Mul menu:\n\t\t1 - to multiply sparse matrixes,\n"
				    "\t\t2 - to multiply ordinary matrixes,\n"
				    "\t\t3 - to multiply both of them\n", "mul", 1, N_MUL_C -1);

				int	rc;
				switch (mul_c) {
				case MB:
					rc = mul_mbc_by_mbr(&mbc1, &mbr2, &mbr_res);
					break;
				case MTX:
					rc = mul_mtxs(&mtx1, &mtx2, &mtx_res);
					break;
				case BOTH:
					rc = mul_mbc_by_mbr(&mbc1, &mbr2, &mbr_res);
					if (rc == 0)
						mul_mtxs(&mtx1, &mtx2, &mtx_res);
					break;
				default:
					break;
				}

				break;
			}
		case EFFICIENCY:
			measure_eff(&mbc1, &mbr2, &mbr_res, &mtx1, &mtx2, &mtx_res);
			break;
		default:
			printf("Wrong command. It must be an integer from 0 to %d."
			    "Try again.\n", curr_n_commands);
			break;
		}
	}
}


void print_menu(char *m[], int n_c)
{
	for (int i = 0; i < n_c; ++i)
		printf("\t\t%s\n", m[i]);
}


void scan_mtx_from_file(mtx *m)
{
	FILE * f;
	char	fname[MAX_STR_LEN];

	while (1) {
		printf("> Enter name of the file to load data from: ");
		if (read_str(stdin, fname, MAX_STR_LEN) < 0) {
			printf("Error while reading a file_name. Try again.\n");
			continue;
		}

		f = fopen(fname, "rb");
		if (f == NULL) {
			printf("Error while opening the file."
			    "Try again with a valid name.\n");
			continue;
		}

		if (fscan_mtx(f, m) != 0) {
			printf("This file is corrupt. Try another one.\n");
			fclose(f);
			continue;
		}

		break;
	}

	fclose(f);
}


int	scan_mtx_from_keyboard(mtx *m, long needed_size)
{
	long	n_c, n_r;
	int	n;

	if (needed_size == 0) {
		while (1) {
			printf("> Enter number of rows of a matrix: ");
			if (read_long(&n_r) != 0 || n_r <= 0)
				printf("Wrong input. Number of rows is an integer bigger than 0."
				    "Try again.\n");
			else
				break;

		}
	} else
		n_r = needed_size;

	while (1) {
		printf("> Enter number of columns of a matrix (number of rows - %ld): ", n_r);
		if (read_long(&n_c) != 0)
			printf("Wrong input. Number of columns is an integer bigger than 0."
			    "Try again.\n");
		else
			break;

	}


	m->n_rows = n_r;
	m->n_cols = n_c;
	mtx_init0(m);


	while (1) {
		printf("> Enter number of elements to init: ");
		if (read_int(&n) != 0 || n <= 0 || n > n_c * n_r)
			printf("Error. Wrong number of elements. Try again.\n");
		else
			break;
	}


	long	cr, cc;
	for (long i = 0; i < n; ++i) {
		printf("> Enter row of an element: ");
		while (read_long(&cr) != 0 || cr <= 0 || cr > n_r)
			printf("Wrong row.  Try again: ");

		printf("> Enter column of an element: ");
		while (read_long(&cc) != 0 || cc <= 0 || cc > n_c)
			printf("Wrong column.  Try again: ");

		printf("> Enter number to insert on [%ld, %ld]: ", cr, cc);
		cc -= 1;
		cr -= 1;
		while (read_int(&m->nums[cr][cc]) != 0 || m->nums[cr][cc] == 0) {
			printf("Wrong number. Try again: \n");
		}
	}


	return 0;
}


int	scan_command(char *menu, char *command_name, int min, int max)
{
	int	c;

	while (1) {
		printf(menu);
		printf("> Enter %s command (integer from %d to %d): ", command_name, min, max);

		if (read_int(&c) != 0 || c < min || c > max)
			printf("Wrong %s command. Please, try again.\n", command_name);
		else
			break;
	}

	return c;
}


int	input_matrixes(mbc *mbc1, mbr *mbr2, mtx *mtx1, mtx *mtx2)
{
	int	input_type;

	for (int mtx_n = 1; mtx_n <= 2; ++mtx_n) {
		printf(">> Inintializing matrix #%d.\n", mtx_n);
		input_type = scan_command("Init menu:\n\t\t1 - input data from file,\n"
		    "\t\t2 - input data from keyboard\n",
		    "input", 1, N_INPUT_C - 1);

		if (input_type == INPUT_FROM_FILE) {
			if (mtx_n == 1) {
				scan_mtx_from_file(mtx1);
				if (mtx_to_mbc(mtx1, mbc1) != 0) {
					printf("Too big matrix. Couldn't allocate memory.\n");
					return MALLOC_ERR;
				}
			} else {
				while (1) {
					scan_mtx_from_file(mtx2);
					if (mtx2->n_rows != mtx1->n_cols) {
						printf("This program is designed to multiply matrixes.\n"
						    "For that number of columns of the first matrix must be equal to\n"
						    "the number of rows of the second one. Please, choose another\n"
						    " file to load data from.\n");
					} else
						break;
				}

				if (mtx_to_mbr(mtx2, mbr2) != 0) {
					printf("Too big matrix. Couldn't allocate memory.\n");
					return MALLOC_ERR;
				}
			}
		} else {
			if (mtx_n == 1) {
				if (scan_mtx_from_keyboard(mtx1, 0) != 0 || mtx_to_mbc(mtx1, mbc1) != 0) {
					printf("Too big matrix. Couldn't allocate memory.\n");
					return MALLOC_ERR;
				}
			} else {
				if (scan_mtx_from_keyboard(mtx2, mtx1->n_cols) != 0 || mtx_to_mbr(mtx2, mbr2) != 0) {
					printf("Too big matrix. Couldn't allocate memory.\n");
					return MALLOC_ERR;
				}
			}
		}
	}

	return 0;
}


#define N_TESTS 50
#define MAX_PERSENT 100
ull	current_time()
{
	struct timespec ts;
	clockid_t clkid;
	clkid = CLOCK_REALTIME;
	clock_gettime(clkid, &ts);

	return ts.tv_sec * 1000000000 + ts.tv_nsec;
}

ull sum(ull *arr, long n) {
	ull s = 0;

	for (long i = 0; i < n; ++i)
		s += arr[i];

	return s;
}

#define STEP 1
void print_eff(ull *avg_mtx, ull *avg_mb, size_t *mem_mtx, size_t *mem_mb)
{
	printf("┌──────────────┬───────────────────────────┬─────────────────────────────┬──────────────────┬────────────────────┐\n"
	       "│  %% of sparse │ Time of mul ord. matrixes │ Time of mul sparse matrixes │    Memory ord.   │   Memory sparse    │\n"  "├──────────────┼───────────────────────────┼─────────────────────────────┼──────────────────┼────────────────────┤\n");
	for (int i = 0; i < MAX_PERSENT; i += STEP)
		printf("│ %11d%% │ %22lld us │ %24lld us │ %10ld bytes │ %12ld bytes │\n", i, avg_mtx[i], avg_mb[i], mem_mtx[i], mem_mb[i]);

	printf("└──────────────┴───────────────────────────┴─────────────────────────────┴──────────────────┴────────────────────┘\n");

}

size_t sizeof_mtx(mtx *m) {
	size_t s = 0;
	s += sizeof(int) * m->n_cols * m->n_rows;
	s += sizeof(m->n_cols);
	s += sizeof(m->n_rows);
	return s;
}

size_t sizeof_mbc(mbc *m) {
	size_t s = 0;
	s += sizeof(int) * m->non_zero_n;
	s += sizeof(long) * m->non_zero_n;
	s += sizeof(long) * m->n_of_rows;
	s += sizeof(m->non_zero_n);
	s += sizeof(m->n_of_rows);
	s += sizeof(m->n_of_cols);
	return s;
}

size_t sizeof_mbr(mbr *m) {
	size_t s = 0;
	s += sizeof(int) * m->non_zero_n;
	s += sizeof(long) * m->non_zero_n;
	s += sizeof(long) * m->n_of_cols;
	s += sizeof(m->non_zero_n);
	s += sizeof(m->n_of_cols);
	s += sizeof(m->n_of_rows);
	return s;
}

void measure_eff(mbc *mbc1, mbr *mbr2, mbr *mbr_res, mtx *mtx1, mtx *mtx2, mtx *mtx_res)
{
	ull	time_mtx[N_TESTS];
	ull	time_mb[N_TESTS];
	ull avg_mtx[MAX_PERSENT];
	ull avg_mb[MAX_PERSENT];
	size_t mem_mtx[MAX_PERSENT];
	size_t mem_mb[MAX_PERSENT];

	for (int persent = 0; persent < MAX_PERSENT; persent += STEP) {
		//free_all(mbc1, mbr2, mbr_res, mtx1, mtx2, mtx_res);
		generate_all(mbc1, mbr2, mtx1, mtx2, persent);

		for (int test = 0; test < N_TESTS; ++test) {
			time_mtx[test] = current_time();
			mul_mtxs(mtx1, mtx2, mtx_res);
			time_mtx[test] = current_time() - time_mtx[test];
		}
		avg_mtx[persent] = sum(time_mtx, N_TESTS) / N_TESTS;

		for (int test = 0; test < N_TESTS; ++test) {
			time_mb[test] = current_time();
			mul_mbc_by_mbr(mbc1, mbr2, mbr_res);
			time_mb[test] = current_time() - time_mb[test];
		}
		avg_mb[persent] = sum(time_mb, N_TESTS) / N_TESTS;

		mem_mtx[persent] = sizeof_mtx(mtx1) + sizeof_mtx(mtx2) + sizeof_mtx(mtx_res);
		mem_mb[persent] = sizeof_mbc(mbc1) + sizeof_mbr(mbr2) + sizeof_mbr(mbr_res);
		//printf("%d\n", persent);
	}

	print_eff(avg_mtx, avg_mb, mem_mtx, mem_mb);
}


void generate_all(mbc *mbc1, mbr *mbr2, mtx *mtx1, mtx *mtx2, int persent)
{
	generate_mtx(mtx1, persent);
	generate_mtx(mtx2, persent);
	mtx_to_mbc(mtx1, mbc1);
	mtx_to_mbr(mtx2, mbr2);
}


void pre_init_all(mbc *mbc1, mbr *mbr2, mbr *mbr_res, mtx *mtx1, mtx *mtx2, mtx *mtx_res)
{
	memset(mbc1, 0, sizeof(mbc));
	memset(mbr2, 0, sizeof(mbr));
	memset(mbr_res, 0, sizeof(mbr));

	memset(mtx1, 0, sizeof(mtx));
	memset(mtx2, 0, sizeof(mtx));
	memset(mtx_res, 0, sizeof(mtx));
}

