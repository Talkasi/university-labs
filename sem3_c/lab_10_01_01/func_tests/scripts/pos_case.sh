#!/bin/bash

# "$1" - file where result is stored by the program
# "$2" - file where expected result is stored
# "$3" - arguments for the program
# "$4" - flags

if [ -z "$2" ] || [ -z "$3" ]; then
    echo "Wrong parameters" >&2
    exit 1
fi

file="$(mktemp)"
command="./app.exe $(cat "$3")"

if [ "$4" == "--mem_check" ] ; then
  valgrind -q --leak-check=full --undef-value-errors=yes $command > /dev/null
fi

$command > /dev/null

if func_tests/scripts/comparator.sh "$1" "$2"; then
    rm "$file"
    exit 0
fi

rm "$file"
exit 1
