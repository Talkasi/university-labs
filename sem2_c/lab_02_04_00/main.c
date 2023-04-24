#include <stdio.h>

#define N_MAX 10

#define INPUT_ARRAY_ERROR 2
#define OVERFLOW_ERROR 100

size_t arr_scan(int arr[], size_t len_max);
void arr_print(int arr[], size_t arr_len);

void bubble_sort(int arr[], size_t arr_len);

int main(void)
{
    int arr[N_MAX];
    size_t arr_len;
    int ret_code = 0;

    printf("Enter elements of an array:\n");
    if ((arr_len = arr_scan(arr, N_MAX)) == 0)
    {
        printf("Input array error.\n");
        return INPUT_ARRAY_ERROR;
    }

    if (arr_len == OVERFLOW_ERROR)
    {
        ret_code = OVERFLOW_ERROR;
        arr_len = N_MAX;
    }

    bubble_sort(arr, arr_len);

    printf("Elements of the new array:\n");
    arr_print(arr, arr_len);

    return ret_code;
}

void bubble_sort(int arr[], size_t arr_len)
{
    for (size_t i = 0; i < arr_len; ++i)
        for (size_t j = 0; j < i; ++j)
            if (arr[i] < arr[j])
            {
                int temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
}

size_t arr_scan(int arr[], size_t len_max)
{
    size_t i = 0;
    int temp;

    while (scanf("%d", &temp) == 1)
    {
        if (i >= len_max)
            return OVERFLOW_ERROR;
        arr[i++] = temp;
    }

    return i;
}

void arr_print(int arr[], size_t arr_len)
{
    for (size_t i = 0; i < arr_len; ++i)
        printf("%d ", arr[i]);
}
