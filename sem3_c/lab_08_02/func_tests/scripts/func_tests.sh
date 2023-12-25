#!/bin/bash

n_failed=0
RED='\033[0;31m'
GREEN='\033[0;32m'
NC='\033[0m'

# Positive tests
echo "> Positive tests"
for in_file in func_tests/data/pos_*_in.txt; do
  test_number=$(echo "$in_file" | grep -o "[0-9]*")
  if [ -z "$test_number" ]; then
    echo "There are no positive tests"
    break
  fi

  out_file="func_tests/data/pos_""$test_number""_out.txt"

  if func_tests/scripts/pos_case.sh "$in_file" "$out_file" "$1"; then
    echo -e "Test ""$test_number"": ${GREEN}PASSED${NC}"
  else
    n_failed=$((n_failed + 1))
    echo -e "Test ""$test_number"": ${RED}FAILED${NC}"
  fi
done

# Negative tests
echo "> Negative tests"
for in_file in func_tests/data/neg_*_in.txt; do
  test_number=$(echo "$in_file" | grep -o "[0-9]*")
  if [ -z "$test_number" ]; then
    echo "There are no negative tests"
    break
  fi

  if func_tests/scripts/neg_case.sh "$in_file" "$1"; then
    echo -e "Test ""$test_number"": ${GREEN}PASSED${NC}"
  else
    n_failed=$((n_failed + 1))
    echo -e "Test ""$test_number"": ${RED}FAILED${NC}"
  fi
done

if [ "$n_failed" -ne "0" ]; then
  exit 1
else
  exit 0
fi
