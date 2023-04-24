#!/bin/bash

gcc -c main.c -Werror -Wall -Wpedantic -Wextra -Wfloat-equal -std=c99 -g3
gcc main.o -o app.exe -lm
