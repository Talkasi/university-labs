#!/bin/bash
echo "────────────── Welcome to the validation tool of the comparator #3! ──────────────"


check() {
	command="$(echo $?)"
	[ $command == "$1" ] && echo -e "[PASSED] $2$3" || echo -e \
	"\n[FAILED] $2$3\n> Expected $1, but $command got.\n"
}


echo -e "─────────── Testing the comparator for errors in the given parameters ────────────\n"

./comparator3.sh > /dev/null 2>&1
check "1" "No parameters are passed."

./comparator3.sh tests3/file1.txt --verbose > /dev/null 2>&1
check "1" "One of the files is not specified. Key --verbose is specified."

./comparator3.sh tests3/file1.txt > /dev/null 2>&1
check "1" "One of the files is not specified. Key --verbose is not specified too."

./comparator3.sh tests3/not_exist.txt tests3/file1.txt > /dev/null 2>&1
check "1" "The first file does not exist."

./comparator3.sh tests3/file1.txt tests3/not_exist.txt > /dev/null 2>&1
check "1" "The second file does not exist."

./comparator3.sh tests3/file1.txt tests3/file1.txt -va > /dev/null 2>&1
check "1" "Key parameter is wrong."

./comparator3.sh tests3/file1.txt tests3/file1.txt --verbose smthing else > /dev/null 2>&1
check "1" "More parameters are being passed than needed."

echo -e "\n────────────────────────── The main comparator #3 tests ──────────────────────────\n"

# Checked
./comparator3.sh tests3/empty_file tests3/empty_file > /dev/null 2>&1
check "1" "Both files are empty."

# Checked
./comparator3.sh tests3/file1.txt tests3/file1.txt > /dev/null 2>&1
check "1" "Files are equal and don't contain float numbers."

# Checked
./comparator3.sh tests3/file3.txt tests3/file3.txt > /dev/null 2>&1
check "0" "Files are not equal but contain equal integer numbers."

# Checked
./comparator3.sh tests3/file4.txt tests3/file5.txt > /dev/null 2>&1
check "0" "Files are different and contain equal float numbers and integers."

# Checked
./comparator3.sh tests3/file6.txt tests3/file7.txt > /dev/null 2>&1
check "0" "Files are different and contain equal float numbers and integers, numbers\n" \
		  "in the words should be ignored."

# Checked
./comparator3.sh tests3/file8.txt tests3/file9.txt > /dev/null 2>&1
check "0" "Files contain equal float numbers and integers, numbers in the words and\n" \
		  "numbers in scientific notation should be ignored."

# Checked
./comparator3.sh tests3/file9.txt tests3/file10.txt > /dev/null 2>&1
check "1" "Files contain equal float numbers and integers with different number of\n" \
		  "zeros in the end."

# Checked
./comparator3.sh tests3/file9.txt tests3/file13.txt > /dev/null 2>&1
check "1" "Files contain different float numbers."

# Checked
./comparator3.sh tests3/file11.txt tests3/file12.txt > /dev/null 2>&1
check "0" "Files contain equal float numbers and integers with leading zeros."

echo -e "\n───────────────────────────── All tests have been run ────────────────────────────" \
		"\n──────────────────────────────────── Good luck! ──────────────────────────────────"
