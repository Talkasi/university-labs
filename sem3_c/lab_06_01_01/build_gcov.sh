#!/bin/bash

gcc -std=c99 -Wall -Werror -Wpedantic -Wextra -Wvla -c -O0 -g3 --coverage main.c my_film.c
gcc  main.o my_film.o -o app.exe --coverage -lm
