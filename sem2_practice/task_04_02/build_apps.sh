#!/bin/bash

files=$(sed -n "1p" options.cfg)
opts=$(sed -n "2p" options.cfg)
sizes=$(sed -n "3p" options.cfg)
n_digits=$(sed -n "4p" options.cfg)

green="\033[32m"
color_off="\033[0m"

echo -ne "$color_off\rBuilding: $green""STARTED""$color_off\n"
for file in $files; do
    for opt in $opts; do
        for size in $sizes; do
                size_prt="$size"
                while [ "${#size_prt}" != "$n_digits" ]; do
                    size_prt="0$size_prt"
                done
                gcc -std=c99 -Wall -Werror -Wpedantic -Wextra \
                    -DN="$size""ULL" \
                    -"$opt" "$file".c -o ./apps/"$file"_"$opt"_"$size_prt".exe
        done
    done
done
echo -ne "$color_off\rBuilding: $green""FINISHED""$color_off\n"
