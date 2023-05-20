#!/bin/bash

files=$(sed -n "1p" options.cfg)
times=$(sed -n "2p" options.cfg)
n_digits=$(sed -n "3p" options.cfg)

count=1
if [ -n "$1" ]; then
    count="$1"
fi

if [ -n "$2" ]; then
    times="$2"
fi

green="\033[32m"
color_off="\033[0m"

i=1
if [ "$i" -lt "$count" ]; then
    echo -ne "$color_off\rUpdating data: $green""STARTED""$color_off\n"
else
    exit 1
fi
while [ "$i" -lt "$count" ]; do
    for file in $files; do
        for time in $times; do
            while [ "${#time}" != "$n_digits" ]; do
                time="0$time"
            done
            ./apps/"$file"_"$time".exe >>./data/"$file"_"$time".txt
        done
    done
    i="$((i + 1))"
done

echo -ne "$color_off\rUpdating data: $green""FINISHED""$color_off\n"
