#!/bin/bash

if [ $# -ne 2 ]; then
    exit 1
fi

program_out=$1
test_out=$2

mask="[+-]?[0-9][0-9]*.?[0-9]*"

program_out_numbers=$(grep -Eo "$mask" "$program_out")
test_out_numbers=$(grep -Eo "$mask" "$test_out")

if [ "$program_out_numbers" != "$test_out_numbers" ]; then
    exit 1
fi

exit 0