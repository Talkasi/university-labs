#!/bin/bash

gcc -c main.c my_film.c -Werror -Wall -Wpedantic -Wextra -Wfloat-equal -std=c99 -g3
gcc main.o my_film.o -o app.exe -lm
