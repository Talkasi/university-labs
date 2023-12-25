#ifndef MY_FILE_H
#define MY_FILE_H
#include <stdio.h>

long fcount_elems(FILE *f);
int fread_data(FILE *f, int *arr_s, int *arr_e);
int fwrite_data(FILE *f, int *arr_s, int *arr_e);

#endif