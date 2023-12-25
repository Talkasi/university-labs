#!/bin/bash
if [ -z "$1" ] ; then
  echo "Wrong parameters" >&2
  exit 1
fi

command="./app.exe $(cat "$1")"

if [ "$2" == "--mem_check" ] ; then
  valgrind -q --leak-check=full --undef-value-errors=yes $command > /dev/null
fi

$command > /dev/null

rc=$(echo -ne $?)
if [ "$rc" -eq 0 ]; then
  exit 1
else
  exit 0
fi
