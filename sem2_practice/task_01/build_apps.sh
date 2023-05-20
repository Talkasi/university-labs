#!/bin/bash

files=$(sed -n "1p" options.cfg)
times=$(sed -n "2p" options.cfg)
n_digits=$(sed -n "3p" options.cfg)

green="\033[32m"
color_off="\033[0m"

echo -ne "$color_off\rBuilding: $green""STARTED""$color_off\n"
for file in $files; do
    for time in $times; do
        time_prt="$time"
        while [ "${#time_prt}" != "$n_digits" ]; do
            time_prt="0$time_prt"
        done
        gcc -Wall -Werror -Wpedantic -Wextra \
            -DTIME="$time""ULL" \
            "$file".c -o ./apps/"$file"_"$time_prt".exe
    done
done
echo -ne "$color_off\rBuilding: $green""FINISHED""$color_off\n"
