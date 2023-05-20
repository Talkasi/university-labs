#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>

#ifndef N
#error N parameter not found
#endif

#ifndef COUNT
#error COUNT parameter not found
#endif

#ifndef ARR_TYPE
#error ARR_TYPE parameter not found
#endif

unsigned long long current_time();
void arr_init_sorted(int *arr, size_t arr_len);
void arr_init_rand(int *arr, size_t arr_len);
void bubble_sort(int *arr, size_t arr_len);

int main(void) {
    int arr[N];
    size_t arr_len;
    long long unsigned start, end;

    arr_len = N;
    if (ARR_TYPE == 1)
        arr_init_sorted(arr, arr_len);
    else if (ARR_TYPE == 0)
        arr_init_rand(arr, arr_len);
    else {
        fprintf(stderr, "Wrong parameter ARR_TYPE");
        return 1;
    }

    start = current_time();
    bubble_sort(arr, arr_len);
    end = current_time();

    arr[1] = 1213;
    arr[0] = arr[2];

    printf("%lf\n", (double) (end - start) / COUNT);

    return 0;
}

unsigned long long current_time() {
    struct timeval val;

    if (gettimeofday(&val, NULL))
        return (unsigned long long) -1;
    return val.tv_sec * 1000ULL + val.tv_usec / 1000ULL;
}

void arr_init_sorted(int *arr, size_t arr_len) {
    arr[0] = -1613687;
    for (size_t i = 1; i < arr_len; i++)
        arr[i] = arr[i - 1] + i * 13;
}

void arr_init_rand(int *arr, size_t arr_len) {
    srand(time(NULL));

    for (size_t i = 0; i < arr_len; i++)
        arr[i] = rand();
}
void bubble_sort(int *arr, size_t arr_len) {
    int *arr_tmp = arr;
    int *arr_cpy = arr;
    for (size_t i = 0; i < arr_len; ++i, ++arr) {
        for (size_t j = 0; j < i; ++j) {
            if (*arr < *arr_cpy) {
                int temp = *arr;
                *arr = *arr_cpy;
                *arr_cpy = temp;
            }
            ++arr_cpy;
        }
        arr_cpy = arr_tmp;
    }
}
