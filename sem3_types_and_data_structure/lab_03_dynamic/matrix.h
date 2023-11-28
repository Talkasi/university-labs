#ifndef MATRIX_H
#define MATRIX_H
#include <stdio.h>

#define MALLOC_ERR 202
#define REALLOC_ERR 203
#define WRONG_BOUNDS 204
#define WRONG_FILE 205
#define WRONG_MTXS_TO_MUL 206
#define SCANF_ERR 207

struct matrix_n_cols {
	int	*nums;
	long	*n_cols;
	long	non_zero_n;

	long	*f_in_rows;

	long	n_of_rows;
	long n_of_cols;
};

struct matrix_n_rows {
	int	*nums;
	long	*n_rows;
	long	non_zero_n;

	long	*f_in_cols;

	long	n_of_cols;
	long n_of_rows;
};

struct matrix {
	int	*nums;
	long	n_rows;
	long	n_cols;
};

typedef struct matrix_n_cols mbc;
typedef struct matrix_n_rows mbr;
typedef struct matrix mtx;


int	realloc_mbc(mbc *m, long non_zero_n, long f_in_rows_n);
int	realloc_mbr(mbr *m, long non_zero_n, long f_in_cols_n);
int	realloc_mtx(mtx *m, long n_r, long n_c);

void	free_mbc(mbc *m);
void	free_mbr(mbr *m);
void	free_mtx(mtx *m);

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

