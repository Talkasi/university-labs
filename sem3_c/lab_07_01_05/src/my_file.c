#include "my_file.h"

long fcount_elems(FILE *f)
{
    long c = 0;
    int num;
    rewind(f);
    while (fscanf(f, "%d", &num) == 1)
        ++c;

    if (feof(f))
        return c;
    return -1;
}

int fread_data(FILE *f, int *arr_s, int *arr_e)
{
    rewind(f);

    for (long i = 0; arr_s + i < arr_e; ++i)
        if (fscanf(f, "%d", arr_s + i) != 1)
            return -1;

    return 0;
}

int fwrite_data(FILE *f, int *arr_s, int *arr_e)
{
    rewind(f);
    for (int *cur = arr_s; cur < arr_e; ++cur)
        if (fprintf(f, "%d ", *cur) < 0)
            return 0;

    return 1;
}