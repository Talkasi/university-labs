#ifndef MATRIX_H
#define MATRIX_H
#include <stdio.h>

#define MALLOC_ERR 202
#define REALLOC_ERR 203
#define WRONG_BOUNDS 204
#define WRONG_FILE 205
#define WRONG_MTXS_TO_MUL 206
#define SCANF_ERR 207

#define MAX_NR 100
#define MAX_NC 100
#define MAX_N MAX_NR * MAX_NC

struct matrix_n_cols {
	int	nums[MAX_N];
	long	n_cols[MAX_N];
	long	non_zero_n;

	long	f_in_rows[MAX_N];

	long	n_of_rows;
	long n_of_cols;
};

struct matrix_n_rows {
	int	nums[MAX_N];
	long	n_rows[MAX_N];
	long	non_zero_n;

	long	f_in_cols[MAX_N];

	long	n_of_cols;
	long n_of_rows;
};

struct matrix {
	int	nums[MAX_NR][MAX_NC];
	long	n_rows;
	long	n_cols;
};

typedef struct matrix_n_cols mbc;
typedef struct matrix_n_rows mbr;
typedef struct matrix mtx;

int	fscan_mtx(FILE *f, mtx *m);

int	mtx_to_mbc(mtx *src, mbc *dst);
int	mtx_to_mbr(mtx *src, mbr *dst);

int	mul_mtxs(mtx *m1, mtx *m2, mtx *res);
int	mul_mbc_by_mbr(mbc *m1, mbr *m2, mbr *res);

void print_mbc(mbc *m);
void print_mbr(mbr *m);
void print_mtx(mtx *m);

void generate_mtx(mtx *m, int persent);
void mtx_init0(mtx *m);

#endif

