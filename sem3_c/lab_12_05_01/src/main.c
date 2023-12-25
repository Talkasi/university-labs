#include "my_arr.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum errs
{
    IN_FILE_OPEN_ERR = 1,
    OUT_FILE_OPEN_ERR,
    WRONG_NARGS_ERR,
    NO_NUMBERS_ERR,
    EMPTY_ARR_ERR,
    FWRITE_ERR,
    WRONG_FILTER_ARG_ERR,
    READING_ERR
};

enum args
{
    IN_FILE = 1,
    OUT_FILE,
    FILTER
};

int check_args(int argc, char *argv[]);

int main(int argc, char *argv[])
{
    int rc;
    if ((rc = check_args(argc, argv)) != 0)
        return rc;

    FILE *in_f = fopen(argv[IN_FILE], "r");
    if (in_f == NULL)
        return IN_FILE_OPEN_ERR;

    long n = fcount_data(in_f);
    if (n <= 0)
    {
        fclose(in_f);
        return NO_NUMBERS_ERR;
    }

    int *arr = malloc(n * sizeof(int));
    if (arr == NULL)
    {
        fclose(in_f);
        return MALLOC_ERR;
    }

    if (fread_data(in_f, arr, arr + n) != 0)
    {
        fclose(in_f);
        free(arr);
        return READING_ERR;
    }

    fclose(in_f);

    int *main_result_s = arr;
    int *main_result_e = arr + n;

    if (argc == 4)
    {
        int *res_s = malloc(n * sizeof(int));
        if (res_s == NULL)
            return MALLOC_ERR;
        int *res_e = res_s + n;

        if ((rc = key(arr, arr + n, &res_s, &res_e)) != 0)
        {
            free(res_s);
            free(arr);
            return rc;
        }

        main_result_s = res_s;
        main_result_e = res_e;

        free(arr);
        arr = NULL;
    }

    mysort(main_result_s, main_result_e - main_result_s, sizeof(int), cmp_ints);

    FILE *out_f = fopen(argv[OUT_FILE], "w");
    if (out_f == NULL)
    {
        free(main_result_s);
        return OUT_FILE_OPEN_ERR;
    }

    if (!fwrite_data(out_f, main_result_s, main_result_e))
    {
        fclose(out_f);
        free(main_result_s);
        return FWRITE_ERR;
    }

    fclose(out_f);
    free(main_result_s);

    return 0;
}

int check_args(int argc, char *argv[])
{
    if (argc != 3 && argc != 4)
        return WRONG_NARGS_ERR;

    if (argc == 4 && strcmp(argv[FILTER], "f") != 0)
        return WRONG_FILTER_ARG_ERR;

    return 0;
}
