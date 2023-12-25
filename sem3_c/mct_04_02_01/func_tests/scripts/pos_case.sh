#!/bin/bash

if [ -z "$1" ] || [ -z "$2" ] ; then
  echo "Wrong parameters" >&2
  exit 1
fi

if [ "$3" == "--mem_check" ] ; then
  valgrind -q --leak-check=full --undef-value-errors=yes ./app.exe < "$1" > /dev/null
fi

file="$(mktemp)"
./app.exe < "$1" > "$file"


if func_tests/scripts/comparator.sh "$file" "$2"; then
  rm "$file"
  exit 0
else
  rm "$file"
  exit 1
fi
