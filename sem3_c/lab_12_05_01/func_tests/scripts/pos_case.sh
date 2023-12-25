#!/bin/bash
# Parameters:
# 1 - "$out_ans_file"
# 2 - "$out_file"
# 3 - "$args_file"
if [ -z "$2" ] || [ -z "$3" ] || [ -z "$4" ]; then
    echo "Wrong parameters" >&2
    exit 1
fi

file="$(mktemp)"
command="./"$4" $(cat "$3")"
$command >"$file"

if [ "$5" == "--mem_check" ] ; then 
  valgrind -q --leak-check=full --undef-value-errors=yes $command >"$file"
fi

if func_tests/scripts/comparator.sh "$1" "$2"; then
    rm "$file"
    exit 0
fi

rm "$file"
exit 1
