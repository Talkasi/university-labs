#!/bin/bash

./clean.sh
echo ">>> Check scripts start"
./check_scripts.sh
echo -e ">>> Check scripts end\n"

echo ">>> Debug"
./build_debug.sh
./func_tests/scripts/func_tests.sh
./clean.sh

echo -e "\n>>> Coverage collector"
./build_gcov.sh
./func_tests/scripts/func_tests.sh
echo
./collect_coverage.sh
./clean.sh

echo -e "\n>>> Address sanitizer"
./build_debug_asan.sh
./func_tests/scripts/func_tests.sh
./clean.sh

echo -e "\n>>> Memory sanitizer"
./build_debug_msan.sh
./func_tests/scripts/func_tests.sh
./clean.sh

echo -e "\n>>> Undefined behavior sanitizer"
./build_debug_ubsan.sh
./func_tests/scripts/func_tests.sh
./clean.sh
