#include <math.h>
#include <stdio.h>

#define INPUT_LENGTH_ERROR 1
#define INPUT_ARRAY_ERROR 2
#define INPUT_NUMBER_ERROR 3

#define N_MAX 2048

int arr_scan(int arr[], size_t arr_len);
void arr_print(int arr[], size_t arr_len);
void my_filter(int arr[], size_t *arr_len);
void my_insertion(int arr[], size_t *arr_len, int number);
void elem_insert(int arr[], size_t *arr_len, int number, size_t position);

int main(void)
{
    size_t arr_len;
    int arr[N_MAX];
    int num;

    printf("Enter length of an array: ");
    if (scanf("%zu", &arr_len) != 1 || arr_len == 0 || arr_len > N_MAX / 2)
    {
        printf("Input length error.\n");
        return INPUT_LENGTH_ERROR;
    }

    printf("Enter elements of an array:\n");
    if (arr_scan(arr, arr_len))
    {
        printf("Input array error.\n");
        return INPUT_ARRAY_ERROR;
    }

    printf("Enter number to insert:\n");
    if (scanf("%d", &num) != 1)
    {
        printf("Input number error.\n");
        return INPUT_NUMBER_ERROR;
    }

    my_filter(arr, &arr_len);
    my_insertion(arr, &arr_len, num);

    arr_print(arr, arr_len);

    return 0;
}

/*
 * Function to scan elements of an array `arr` from the stdin.
 * If an error occurs or EOF found, 1 is returned as an error code.
 * Otherwise, 0 is returned as a success code.
 *
 * It is the caller's responsibility to match the length of an array to the value `arr_len`.
 */
int arr_scan(int arr[], size_t arr_len)
{
    for (size_t i = 0; i < arr_len; ++i)
        if (scanf("%d", &arr[i]) != 1)
            return 1;

    return 0;
}

/*
 * Function to print elements of an array `arr` to the stdout.
 * Each element is separated from others by spase.
 *
 * It is the caller's responsibility to match the length of an array to the value `arr_len`.
 */
void arr_print(int arr[], size_t arr_len)
{
    for (size_t i = 0; i < arr_len; ++i)
        printf("%d ", arr[i]);
}

/*
 * Function to filter array `arr` with all square elements.
 * New length of an array is set to the given length pointer `*arr_len`.
 *
 * It is the caller's responsibility to match the length of an array to the value `arr_len`.
 */
void my_filter(int arr[], size_t *arr_len)
{
    size_t j = 0;

    for (size_t i = 0; i < *arr_len; ++i)
    {
        if (arr[i] >= 0)
        {
            int sq = (int)sqrt(arr[i]);
            if (sq * sq == arr[i])
                arr[j++] = arr[i];
        }
    }

    *arr_len = j;
}

/*
 * Function to insert `number` after each two-digit element in an array `arr`.
 * Length of an array is incremented by the number of inserted elements through the length pointer `*arr_len`.
 *
 * It is the caller's responsibility:
 * - to match the length of an array to the value `arr_len`;
 * - to check if there is enough space to insert new elements in an array.
 */
void my_insertion(int arr[], size_t *arr_len, int number)
{
    size_t i = 0;

    while (i < *arr_len)
    {
        if (arr[i] >= 10 && arr[i] < 100)
        {
            elem_insert(arr, arr_len, number, i + 1);
            ++i;
        }

        ++i;
    }
}

/*
 * Function to insert `number` on the `position` in an array `arr`.
 * When the element is inserted, length of an array is incremented by one through the pointer.
 *
 * It is the caller's responsibility:
 * - to match the length of an array to the value `arr_len`;
 * - to check if there is enough space to insert new element in an array;
 * - to check if the position value is within the bounds of an array:
 * > If position value is equal to the length of an array, element would be inserted correctly.
 * > If position value is bigger than the length of an array, function behavior is undefined.
 */
void elem_insert(int arr[], size_t *arr_len, int number, size_t position)
{
    for (size_t i = *arr_len; i > position; --i)
        arr[i] = arr[i - 1];

    arr[position] = number;
    ++*arr_len;
}
