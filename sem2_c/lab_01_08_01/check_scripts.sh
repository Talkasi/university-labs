#!/bin/bash

for script in ./*.sh ./func_tests/scripts/*.sh; do
  shellcheck "$script"
done
