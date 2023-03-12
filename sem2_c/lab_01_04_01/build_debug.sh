#!/bin/bash

gcc -c main.c -Werror -Wall -Wpedantic -Wextra -Wfloat-equal -std=c99
gcc main.o -o app.exe
