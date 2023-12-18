#ifndef INPUT_H
#define INPUT_H
#include <stdio.h>

#define MAX_INT_LEN 21
#define MAX_STR_LEN 256

int read_int(int *number);
int read_long(long *number);
int read_str(FILE *f, char *s, int max_len);
int read_char(char *c);
int read_double(double *number);

#endif