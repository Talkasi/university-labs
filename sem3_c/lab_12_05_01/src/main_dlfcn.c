#include <dlfcn.h>
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
    READING_ERR,
    LIB_LOAD_ERR,
    FUNC_LOAD_ERR,
    MALLOC_ERR
};

enum args
{
    IN_FILE = 1,
    OUT_FILE,
    FILTER
};

typedef int (*fn_cmp_ints_t)(const void *, const void *);
typedef int (*fn_key_t)(const int *, const int *, int **, int **);
typedef void (*fn_mysort_t)(void *, size_t, size_t, int (*compare)(const void *, const void *));
typedef long (*fn_fcount_data_t)(FILE *);
typedef int (*fn_fread_data_t)(FILE *, int *, int *);
typedef int (*fn_fwrite_data_t)(FILE *, int *, int *);

typedef struct
{
    fn_cmp_ints_t cmp_ints;
    fn_key_t key;
    fn_mysort_t mysort;
    fn_fcount_data_t fcount_data;
    fn_fread_data_t fread_data;
    fn_fwrite_data_t fwrite_data;
} lib_funcs_t;

int check_args(int argc, char *argv[]);
int load_lib_func(void *hlib, void **func, char *func_name);
int load_lib_funcs(void *hlib, lib_funcs_t *lib_funcs);

int main(int argc, char *argv[])
{
    int rc;
    if ((rc = check_args(argc, argv)) != 0)
        return rc;

    void *hlib = dlopen("./libarr_dyn.so", RTLD_NOW);
    if (hlib == NULL)
    {
        printf("%s\n", dlerror());
        return LIB_LOAD_ERR;
    }

    lib_funcs_t lib_funcs;
    if (load_lib_funcs(hlib, &lib_funcs))
    {
        dlclose(hlib);
        return FUNC_LOAD_ERR;
    }
    dlclose(hlib);

    FILE *in_f = fopen(argv[IN_FILE], "r");
    if (in_f == NULL)
        return IN_FILE_OPEN_ERR;

    long n = lib_funcs.fcount_data(in_f);
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

    if (lib_funcs.fread_data(in_f, arr, arr + n) != 0)
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
        main_result_s = malloc(n * sizeof(int));
        if (main_result_s == NULL)
            return MALLOC_ERR;
        main_result_e = main_result_s + n;

        if ((rc = lib_funcs.key(arr, arr + n, &main_result_s, &main_result_e)) != 0)
        {
            free(main_result_s);
            free(arr);
            return rc;
        }

        free(arr);
        arr = NULL;
    }

    lib_funcs.mysort(main_result_s, main_result_e - main_result_s, sizeof(int), lib_funcs.cmp_ints);

    FILE *out_f = fopen(argv[OUT_FILE], "w");
    if (out_f == NULL)
    {
        free(main_result_s);
        return OUT_FILE_OPEN_ERR;
    }

    if (!lib_funcs.fwrite_data(out_f, main_result_s, main_result_e))
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

int load_lib_func(void *hlib, void **func, char *func_name)
{
    *func = dlsym(hlib, func_name);
    if (*func == NULL)
    {
        printf("%s\n", dlerror());
        return FUNC_LOAD_ERR;
    }

    return 0;
}

int load_lib_funcs(void *hlib, lib_funcs_t *lib_funcs)
{
    int rc = 0;
    rc += load_lib_func(hlib, (void **)&lib_funcs->cmp_ints, "cmp_ints");
    rc += load_lib_func(hlib, (void **)&lib_funcs->key, "key");
    rc += load_lib_func(hlib, (void **)&lib_funcs->mysort, "mysort");
    rc += load_lib_func(hlib, (void **)&lib_funcs->fcount_data, "fcount_data");
    rc += load_lib_func(hlib, (void **)&lib_funcs->fread_data, "fread_data");
    rc += load_lib_func(hlib, (void **)&lib_funcs->fwrite_data, "fwrite_data");
    return rc;
}
