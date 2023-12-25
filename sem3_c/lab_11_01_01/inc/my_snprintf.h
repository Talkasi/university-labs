#ifndef MY_SNPRINTF_H
#define MY_SNPRINTF_H
#include <stdarg.h>
#include <stdio.h>

int my_snprintf(char *str, size_t size, const char *format, ...);
int my_vsnprintf(char *str, size_t size, const char *format, va_list arg);

#endif
