#!/bin/bash

for args_file in "01" "02" "03" "04" "05" "06" "07" "08" "09" "10" "11" ; do
    touch "../data/neg_""$args_file""_in.txt"
    touch "../data/pos_""$args_file""_in.txt"
done
