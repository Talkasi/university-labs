#include <stdio.h>

#define N_MAX 10

#define INPUT_LEN_ERROR 1
#define INPUT_ARRAY_ERROR 2
#define NO_ODDS_ERROR 3

int arr_scan(int arr[], size_t arr_len);
int product_of_odds(int arr[], size_t arr_len);

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
    if (arr_scan(arr, arr_len))
    {
        printf("Input array error.\n");
        return INPUT_ARRAY_ERROR;
    }

    int product = product_of_odds(arr, arr_len);
    if (product == 0)
    {
        printf("Error: there are no odd elements in the given array.\n");
        return NO_ODDS_ERROR;
    }

    printf("The product of odd array elements is: %d\n", product);
    return 0;
}

int arr_scan(int arr[], size_t arr_len)
{
    for (size_t i = 0; i < arr_len; ++i)
        if (scanf("%d", &arr[i]) != 1)
            return 1;

    return 0;
}

int product_of_odds(int arr[], size_t arr_len)
{
    int product = 1;
    int n_odds = 0;

    for (size_t i = 0; i < arr_len; ++i)
        if (arr[i] % 2 != 0)
        {
            ++n_odds;
            product *= arr[i];
        }

    if (n_odds == 0)
        return 0;

    return product;
}
