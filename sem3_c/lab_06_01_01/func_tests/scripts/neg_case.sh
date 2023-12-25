#!/bin/bash

if [ -z "$1" ] ; then
  echo "Wrong parameters" >&2
  exit 1
fi

command="./app.exe $(cat "$1")"

if $command > /dev/null; then
  exit 1
else
  exit 0
fi
