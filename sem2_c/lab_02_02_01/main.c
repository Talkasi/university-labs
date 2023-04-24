#include <stdio.h>

#define N_MAX 10

#define INPUT_LEN_ERROR 1
#define INPUT_ARRAY_ERROR 2
#define NO_PRIMES_ERROR 3

int arr_scan(int arr[], size_t arr_len);
void arr_print(int arr[], size_t arr_len);

int is_prime(int number);
size_t arr_primes_copy(int dst[], int src[], size_t src_len);

int main(void)
{
    int arr[N_MAX];
    size_t arr_len;
    int cp_arr[N_MAX];
    size_t cp_arr_len;

    printf("Enter number of elements in an array: ");
    if (scanf("%zu", &arr_len) != 1 || arr_len == 0 || arr_len > N_MAX)
    {
        printf("Input length error.\n");
        return INPUT_LEN_ERROR;
    }

    printf("Enter elements of an array:\n");
    if (arr_scan(arr, arr_len))
    {
        printf("Input array error.\n");
        return INPUT_ARRAY_ERROR;
    }

    cp_arr_len = arr_primes_copy(cp_arr, arr, arr_len);

    if (cp_arr_len == 0)
    {
        printf("Error: there are no prime numbers in the given array.\n");
        return NO_PRIMES_ERROR;
    }

    printf("Elements of the new array:\n");
    arr_print(cp_arr, cp_arr_len);

    return 0;
}

int is_prime(int number)
{
    if (number == 2)
        return 1;

    if (number <= 1 || number % 2 == 0)
        return 0;

    int temp = number;
    for (int i = 3; temp - i > 0; i += 2, temp -= i)
        if (number % i == 0)
            return 0;

    return 1;
}

size_t arr_primes_copy(int dst[], int src[], size_t src_len)
{
    size_t dst_len = 0;

    for (size_t i = 0; i < src_len; ++i)
        if (is_prime(src[i]))
            dst[dst_len++] = src[i];

    return dst_len;
}

int arr_scan(int arr[], size_t arr_len)
{
    for (size_t i = 0; i < arr_len; ++i)
        if (scanf("%d", &arr[i]) != 1)
            return 1;

    return 0;
}

void arr_print(int arr[], size_t arr_len)
{
    for (size_t i = 0; i < arr_len; ++i)
        printf("%d ", arr[i]);
}
