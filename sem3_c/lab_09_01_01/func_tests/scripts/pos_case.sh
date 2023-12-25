#!/bin/bash

if [ -z "$1" ] || [ -z "$2" ] ; then
  echo "Wrong parameters" >&2
  exit 1
fi


command="./app.exe $(cat "$2")"
file="$(mktemp)"
if [ "$3" == "--mem_check" ] ; then
  valgrind -q --leak-check=full --undef-value-errors=yes $command > "$file"
fi

$command > "$file"

if func_tests/scripts/comparator.sh "$file" "$1"; then
  rm "$file"
  exit 0
else
  rm "$file"
  exit 1
fi