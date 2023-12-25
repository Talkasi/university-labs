#!/bin/bash

if [ -z "$1" ] ; then
    echo "Wrong parameter" >&2
    exit 1
fi

n_suites=$(("$1" + 1))

MAX_INT_N_BITS=64

RED='\033[0;31m'
GREEN='\033[0;32m'
NC='\033[0m'

if [ "$2" == "--mem_check" ] ; then 
    valgrind -q --leak-check=full --undef-value-errors=yes ./unit_tests.exe > /dev/null
fi

./unit_tests.exe
RC=$(echo $?)

curr_suite=1
while [ "$curr_suite" -lt "$n_suites" ]; do
    cur_n_failed=$((RC % MAX_INT_N_BITS))
    if [ $cur_n_failed -eq 0 ] ; then 
        echo -e "SUITE #""$curr_suite"": ${GREEN} ""$cur_n_failed"" FAILED${NC}"
    else
        echo -e "SUITE #""$curr_suite"": ${RED} ""$cur_n_failed"" FAILED${NC}"
    fi
    RC=$((RC / MAX_INT_N_BITS))
    curr_suite="$((curr_suite + 1))"
done

exit 0
