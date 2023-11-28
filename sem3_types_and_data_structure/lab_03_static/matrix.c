#include "matrix.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdlib.h>
#include <sys/param.h>

void mtx_init0(mtx *m) {
	for (long i = 0; i < m->n_rows; ++i)
		for (long j = 0; j < m->n_cols; ++j)
			m->nums[i][j] = 0;
}

#define GENERATE_ROW 50
#define GENERATE_COL 50
void generate_mtx(mtx *m, int persent)
{
	m->n_rows = GENERATE_ROW;
	m->n_cols = GENERATE_COL;
	mtx_init0(m);

	long	n_nums = GENERATE_COL * GENERATE_ROW * (100 - persent) / 100;

	srand(time(NULL));

	long	r, c;
	int	n;
	long n_ins = 0;
	for (long i = 0; i < n_nums; ++i) {
		r = rand() % GENERATE_ROW;
		c = rand() % GENERATE_COL;
		if (m->nums[r][c] == 0) {
			++n_ins;

			n = rand();
			if (n == 0)
				m->nums[r][c] = -1;
			else
				m->nums[r][c] = n;
		}
	}

	for (long i = 0; i < GENERATE_ROW && n_ins != n_nums; ++i)
		for (long j = 0; j < GENERATE_COL && n_ins != n_nums; ++j) {
			if (m->nums[i][j] == 0) {
				n = rand();
				if (n == 0)
					m->nums[r][c] = -1;
				else
					m->nums[r][c] = n;
				++n_ins;
			}
		}
}


int	fscan_bounds(FILE *f, long *r, long *c)
{
	rewind(f);
	if (fread(r, sizeof(long), 1, f) != 1 || r <= 0)
		return WRONG_BOUNDS;
	if (fread(c, sizeof(long), 1, f) != 1 || c <= 0)
		return WRONG_BOUNDS;

	return 0;
}

int	fscan_mtx(FILE *f, mtx *m)
{
	long	nr, nc;

	int	rc;
	if ((rc = fscan_bounds(f, &nr, &nc)) != 0)
		return rc;

	if (fread(m->nums, sizeof(int[nr][nc]), 1, f) != 1)
		return WRONG_FILE;

	m->n_cols = nc;
	m->n_rows = nr;

	return 0;
}


int	mcount_non_zero(mtx *m)
{
	long	non_zero_n = 0;

	for (long i = 0; i < m->n_rows; ++i)
		for (long j = 0; j < m->n_cols; ++j)
			if (m->nums[i][j] != 0)
				++non_zero_n;

	return non_zero_n;
}


int	mtx_to_mbr(mtx *src, mbr *dst)
{
	dst->non_zero_n = mcount_non_zero(src);
	dst->n_of_cols = src->n_cols;
	dst->n_of_rows = src->n_rows;
	long	non_zero_i = 0;
	long	f_in_cols_i = 0;
	long	prev_col = -1;
	long	j;

	for (j = 0; j < src->n_cols; ++j) {
		for (long i = 0; i < src->n_rows; ++i) {
			if (src->nums[i][j] != 0) {
				dst->nums[non_zero_i] = src->nums[i][j];
				dst->n_rows[non_zero_i] = i;

				while (j > prev_col && j - prev_col != 1) {
					dst->f_in_cols[f_in_cols_i++] = -1;
					++prev_col;
				}

				if (j > prev_col) {
					dst->f_in_cols[f_in_cols_i++] = non_zero_i;
					prev_col = j;
				}

				++non_zero_i;
			}
		}
	}

	if (prev_col == -1) {
		prev_col = 0;
		non_zero_i = -1;
	}

	if (j != prev_col)
		while (j - prev_col != 1) {
			dst->f_in_cols[f_in_cols_i++] = -1;
			++prev_col;
		}

	//print_mbr(dst);
	return 0;
}


int	mtx_to_mbc(mtx *src, mbc *dst)
{
	dst->non_zero_n = mcount_non_zero(src);
	dst->n_of_rows = src->n_rows;
	dst->n_of_cols = src->n_cols;
	long	non_zero_i = 0;
	long	f_in_rows_i = 0;
	long	prev_row = -1;

	long	i;
	for (i = 0; i < src->n_rows; ++i) {
		for (long j = 0; j < src->n_cols; ++j) {
			if (src->nums[i][j] != 0) {
				dst->nums[non_zero_i] = src->nums[i][j];
				dst->n_cols[non_zero_i] = j;

				while (i > prev_row && i - prev_row != 1) {
					dst->f_in_rows[f_in_rows_i++] = -1;
					++prev_row;
				}

				if (i > prev_row) {
					dst->f_in_rows[f_in_rows_i++] = non_zero_i;
					prev_row = i;
				}
				++non_zero_i;
			}
		}
	}

	if (prev_row == -1)
		prev_row = 0;

	if (i != prev_row)
		while (i - prev_row != 1) {
			dst->f_in_rows[f_in_rows_i++] = -1;
			++prev_row;
		}

	//print_mbc(dst);
	return 0;
}


int	mul_mtxs(mtx *m1, mtx *m2, mtx *res)
{
	if (m1->n_cols != m2->n_rows)
		return WRONG_MTXS_TO_MUL;

	res->n_rows = m1->n_rows;
	res->n_cols = m2->n_cols;

	for (long i = 0; i < m1->n_rows; ++i)
		for (long j = 0; j < m2->n_cols; ++j) {
			res->nums[i][j] = 0;
			for (long k = 0; k < m1->n_cols; ++k)
				res->nums[i][j] += m1->nums[i][k] * m2->nums[k][j];
		}

	return 0;
}

int are_nums_in_m1(mbc *m1, long cur_f1, long i1) {
	long cur_f1_i;
	for (cur_f1_i = cur_f1 + 1; cur_f1 < m1->n_of_rows; ++cur_f1_i)
		if (m1->f_in_rows[cur_f1_i] != -1)
			break;

	if (cur_f1_i < m1->n_of_rows && i1 < m1->f_in_rows[cur_f1_i])
		return 1;

	if (cur_f1_i == m1->n_of_rows && i1 < m1->non_zero_n)
		return 1;

	return 0;
}

int are_nums_in_m2(mbr *m2, long cur_f2, long i2) {
	long cur_f2_i;
	for (cur_f2_i = cur_f2 + 1; cur_f2 < m2->n_of_cols; ++cur_f2_i)
		if (m2->f_in_cols[cur_f2_i] != -1)
			break;

	if (cur_f2_i < m2->n_of_cols && i2 < m2->f_in_cols[cur_f2_i])
		return 1;

	if (cur_f2_i == m2->n_of_cols && i2 < m2->non_zero_n)
		return 1;

	return 0;
}

int	mul_mbc_by_mbr(mbc *m1, mbr *m2, mbr *res)
{
	//printf("Allocating for mb mul\n");
	//print_mbc(m1);
	//printf("----\n");
	//print_mbr(m2);
	//printf("----\n");

	long	cur_f1 = 0;
	long	cur_f2 = 0;
	long	i1 = -1;
	long	i2 = -1;
	long	i_res = 0;
	res->f_in_cols[0] = 0;
	res->nums[0] = 0;
	int non_zero_flag = 0;

	while (1) {
		if (m1->f_in_rows[cur_f1] != -1 && m2->f_in_cols[cur_f2] != -1) {
			while (are_nums_in_m1(m1, cur_f1, i1) &&
				   are_nums_in_m2(m2, cur_f2, i2)) {
				if (m1->n_cols[i1] == m2->n_rows[i2]) {
					res->nums[i_res] += m1->nums[i1] * m2->nums[i2];
					++i1;
					++i2;
				} else if (m1->n_cols[i1] > m2->n_rows[i2])
					++i2;
				else
					++i1;
			}
		}

		if (res->nums[i_res] != 0) {
			non_zero_flag = 1;
			res->n_rows[i_res] = cur_f1;
			++i_res;
			res->nums[i_res] = 0;
		}

		if (cur_f1 + 1 < m1->n_of_rows) {
			i1 = m1->f_in_rows[++cur_f1];
			i2 = m2->f_in_cols[cur_f2];
		} else {
			cur_f1 = 0;
			i1 = m1->f_in_rows[0];
			if (non_zero_flag == 0)
				res->f_in_cols[cur_f2] = -1;
			non_zero_flag = 0;

			if (cur_f2 + 1 < m2->n_of_cols) {
				i2 = m2->f_in_cols[++cur_f2];
			} else {
				break;
			}

			res->f_in_cols[cur_f2] = i_res;
		}
	}

	res->non_zero_n = i_res;
	res->n_of_cols = m2->n_of_cols;

	return 0;
}


void print_mbc(mbc *m)
{
	if (m->non_zero_n == 0) {
		printf("This matrix is empty.\n");
		return;
	}

	long	i = 0;
	printf("Numbers:\n");
	while (i < m->non_zero_n) {
		printf("%d%s", m->nums[i], i + 1 == m->non_zero_n ? "\n" : ", ");
		++i;
	}

	i = 0;
	printf("N cols:\n");
	while (i < m->non_zero_n) {
		printf("%ld%s", m->n_cols[i], i + 1 == m->non_zero_n ? "\n" : ", ");
		++i;
	}

	i = 0;
	printf("N first in rows:\n");
	while (i < m->n_of_rows) {
		printf("%ld%s", m->f_in_rows[i], i + 1 == m->n_of_rows ? "\n" : ", ");
		++i;
	}
}


void print_mbr(mbr *m)
{
	if (m->non_zero_n == 0) {
		printf("This matrix is empty.\n");
		return;
	}

	long	i = 0;
	printf("Numbers:\n");
	while (i < m->non_zero_n) {
		printf("%d%s", m->nums[i], i + 1 == m->non_zero_n ? "\n" : ", ");
		++i;
	}

	i = 0;
	printf("N rows:\n");
	while (i < m->non_zero_n) {
		printf("%ld%s", m->n_rows[i], i + 1 == m->non_zero_n ? "\n" : ", ");
		++i;
	}

	i = 0;
	printf("N first in cols:\n");
	while (i < m->n_of_cols) {
		printf("%ld%s", m->f_in_cols[i], i + 1 == m->n_of_cols ? "\n" : ", ");
		++i;
	}
}


void print_mtx(mtx *m)
{
	if (m->n_rows == 0) {
		printf("This matrix is empty.\n");
		return;
	}

	for (size_t i = 0; i < m->n_rows; ++i) {
		for (size_t j = 0; j < m->n_cols; ++j)
			printf("%10d ", m->nums[i][j]);
		printf("\n");
	}
}


