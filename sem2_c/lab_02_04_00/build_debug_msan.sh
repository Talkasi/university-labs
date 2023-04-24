#!/bin/bash

clang -std=c99 -Wall -Wpedantic -Wextra -Wfloat-equal -fsanitize=memory -fPIE -pie -Wfloat-conversion -fno-omit-frame-pointer -g main.c -o app.exe -lm
