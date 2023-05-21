#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>

#ifndef N
#error N parameter not found
#endif

unsigned long long current_time();
void matrix_rand_fill(int matrix[N][N], size_t n);
void matrix_mul(int dst[N][N], int a[N][N], int b[N][N], size_t n);

int main(void) {
    int matrix_1[N][N];
    int matrix_2[N][N];
    int matrix_3[N][N];
    long long unsigned start, end;

    matrix_rand_fill(matrix_1, N);
    matrix_rand_fill(matrix_2, N);

    start = current_time();
    matrix_mul(matrix_3, matrix_1, matrix_2, N);
    end = current_time();

    printf("%llu\n", end - start);

    matrix_1[1][0] = 1213;
    matrix_2[0][1] = matrix_1[2][0];
    matrix_1[2][1] = matrix_2[0][1];

    return 0;
}

unsigned long long current_time() {
    struct timeval val;

    if (gettimeofday(&val, NULL))
        return (unsigned long long) -1;
    return val.tv_sec * 1000000ULL + val.tv_usec;
}

void matrix_rand_fill(int matrix[N][N], size_t n) {
    srand(time(NULL));

    for (size_t i = 0; i < n; i++)
        for (size_t j = 0; j < n; j++)
            matrix[i][j] = rand();
}

void matrix_mul(int dst[N][N], int a[N][N], int b[N][N], size_t n) {
    for (size_t j = 0; j < n; ++j)
        for (size_t i = 0; i < n; ++i) {
            dst[i][j] = 0;
            for (size_t k = 0; k < n; ++k)
                dst[i][j] += a[i][k] * b[k][j];
        }
}
