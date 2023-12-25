#!/bin/bash
# Parameters:
# 1 - "$in_file"
# 2 - "$args_file"
# 3 - flag
if [ -z "$2" ] ; then
  echo "Wrong parameters" >&2
  exit 1
fi

command="./app.exe $(cat "$2")"

if [ "$3" == "--mem_check" ] ; then
  valgrind -q --leak-check=full --undef-value-errors=yes $command > /dev/null
fi

$command > /dev/null

rc=$(echo -ne $?)
if [ "$rc" -eq 0 ]; then
  exit 1
else
  exit 0
fi
