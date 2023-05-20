#!/bin/bash

files=$(sed -n "1p" options.cfg)
opts=$(sed -n "2p" options.cfg)
sizes=$(sed -n "3p" options.cfg)
n_digits=$(sed -n "4p" options.cfg)
types=$(sed -n "5p" options.cfg)

count=1

if [ -n "$1" ]; then
    count="$1"
fi

if [ -n "$2" ]; then
    sizes="$2"
fi

if [ -n "$3" ]; then
    opts="$3"
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
        for opt in $opts; do
            for size in $sizes; do
                for type in $types; do
                    while [ "${#size}" != "$n_digits" ]; do
                        size="0$size"
                    done
                    ./apps/"$file"_"$opt"_"$size"_"$type".exe >>./data/"$file"_"$opt"_"$size"_"$type".txt
                done
            done
        done
    done
    i="$((i + 1))"
done

echo -ne "$color_off\rUpdating data: $green""FINISHED""$color_off\n"
