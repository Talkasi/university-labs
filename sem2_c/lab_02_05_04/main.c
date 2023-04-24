#include <stdio.h>

#define N_MAX 10

#define INPUT_LEN_ERROR 1
#define INPUT_ARRAY_ERROR 2

int arr_scan(int *arr_first, int *arr_past_last);
size_t uniq_count(int *arr_first, int *arr_past_last);
int presence_check(int *arr_first, int *arr_check);

int main(void)
{
    int arr[N_MAX];
    size_t arr_len;

    printf("Enter number of elements in an array: ");
    if (scanf("%zu", &arr_len) != 1 || arr_len == 0 || arr_len > N_MAX)
    {
        printf("Input length error.\n");
        return INPUT_LEN_ERROR;
    }

    printf("Enter elements of an array:\n");
    if (arr_scan(arr, arr + arr_len))
    {
        printf("Input array error.\n");
        return INPUT_ARRAY_ERROR;
    }

    printf("There are %zu uniq elements in the array.\n", uniq_count(arr, arr + arr_len));

    return 0;
}

int arr_scan(int *arr_first, int *arr_past_last)
{
    for (int *arr_cur = arr_first; arr_cur < arr_past_last; ++arr_cur)
        if (scanf("%d", arr_cur) != 1)
            return 1;

    return 0;
}

size_t uniq_count(int *arr_first, int *arr_past_last)
{
    size_t n_uniq = 0;

    for (int *arr_cur = arr_first; arr_cur < arr_past_last; ++arr_cur)
        if (!presence_check(arr_first, arr_cur))
            ++n_uniq;

    return n_uniq;
}

int presence_check(int *arr_first, int *arr_check)
{
    for (int *arr_cur = arr_first; arr_cur < arr_check; ++arr_cur)
        if (*arr_cur == *arr_check)
            return 1;

    return 0;
}
