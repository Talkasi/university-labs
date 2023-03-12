#!/bin/bash

if [ $# -ne 2 ]; then
    exit 1
fi

if cmp "$1" "$2"; then
    exit 0
fi

exit 1