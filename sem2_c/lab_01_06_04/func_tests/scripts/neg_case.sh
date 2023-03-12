#!/bin/bash

if [ -z "$1" ] ; then
  echo "Wrong parameter" >&2
  exit 1
fi

if ./app.exe < "$1" > /dev/null; then
  exit 1
else
  exit 0
fi
