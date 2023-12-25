#!/bin/bash

if [ -z "$1" ] ; then
  echo "Wrong parameter" >&2
  exit 1
fi

if [ "$2" == "--mem_check" ] ; then
  valgrind -q --leak-check=full --undef-value-errors=yes ./app.exe < "$1" > /dev/null
fi

if ./app.exe < "$1" > /dev/null; then
  exit 1
else
  exit 0
fi
