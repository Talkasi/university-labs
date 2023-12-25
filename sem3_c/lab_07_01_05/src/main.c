#include "my_arr.h"
#include "my_file.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define IN_FILE_OPEN_ERR 1
#define OUT_FILE_OPEN_ERR 2
#define WRONG_NARGS_ERR 3
#define NO_NUMBERS_ERR 4
#define EMPTY_ARR_ERR 5
#define FWRITE_ERR 6
#define WRONG_FILTER_ARG_ERR 7
#define READING_ERR 8

#define IN_FILE 1
#define OUT_FILE 2
#define FILTER 3

int check_args(int argc, char *argv[]);

int main(int argc, char *argv[])
{
    int rc;
    if ((rc = check_args(argc, argv)) != 0)
        return rc;

    FILE *in_f = fopen(argv[IN_FILE], "r");
    if (in_f == NULL)
        return IN_FILE_OPEN_ERR;

    long n = fcount_elems(in_f);
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

    int *res_s = arr, *res_e = arr + n;
    if (argc == 4)
    {
        if ((rc = key(arr, arr + n, &res_s, &res_e)) != 0)
        {
            free(arr);
            return rc;
        }
    }

    mysort(res_s, res_e - res_s, sizeof(int), cmp_ints);

    FILE *out_f = fopen(argv[OUT_FILE], "w");
    if (out_f == NULL)
    {
        free(res_s);
        return OUT_FILE_OPEN_ERR;
    }

    if (!fwrite_data(out_f, res_s, res_e))
    {
        fclose(out_f);
        free(res_s);
        return FWRITE_ERR;
    }

    fclose(out_f);
    if (res_s != arr)
    {
        free(res_s);
        free(arr);
    }
    else
        free(res_s);

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
