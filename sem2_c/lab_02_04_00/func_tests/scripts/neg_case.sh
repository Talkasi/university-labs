#!/bin/bash

if [ -z "$1" ] ; then
  echo "Wrong parameter" >&2
  exit 1
fi

file="$(mktemp)"
./app.exe < "$1" > "$file"

if ./app.exe < "$1" > /dev/null; then
  exit 1
else
  if func_tests/scripts/comparator.sh "$file" "$2"; then
    rm "$file"
    exit 0
  else
    rm "$file"
    exit 1
  fi
fi

