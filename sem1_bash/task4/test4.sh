#!/bin/bash
echo "────────────── Welcome to the validation tool of the comparator #4! ──────────────"


check() {
	command="$(echo $?)"
	[ $command == "$1" ] && echo -e "[PASSED] $2$3" || echo -e \
	"\n[FAILED] $2$3\n> Expected $1, but $command got.\n"
}


echo -e "─────────── Testing the comparator for errors in the given parameters ────────────\n"

./comparator4.sh > /dev/null 2>&1
check "1" "No parameters are passed."

./comparator4.sh tests4/file1.txt --verbose > /dev/null 2>&1
check "1" "One of the files is not specified. Key --verbose is specified."

./comparator4.sh tests4/file1.txt > /dev/null 2>&1
check "1" "One of the files is not specified. Key --verbose is not specified too."

./comparator4.sh tests4/not_exist.txt tests4/file1.txt > /dev/null 2>&1
check "1" "The first file does not exist."

./comparator4.sh tests4/file1.txt tests4/not_exist.txt > /dev/null 2>&1
check "1" "The second file does not exist."

./comparator4.sh tests4/not_readable.txt tests4/file1.txt > /dev/null 2>&1
check "1" "No permissions to read the first file."

./comparator4.sh tests4/file1.txt tests4/not_readable.txt > /dev/null 2>&1
check "1" "No permissions to read the second file."

./comparator4.sh tests4/file1.txt tests4/file1.txt -va > /dev/null 2>&1
check "1" "Key parameter is wrong."

./comparator4.sh tests4/file1.txt tests4/file1.txt --verbose smthing else > /dev/null 2>&1
check "1" "More parameters are being passed than needed."

old_IFS=$IFS 
IFS=" "

echo -e "\n────────────────────────── The main comparator #4 tests ──────────────────────────"
echo -e "────────────────────────────────── IFS is a space ────────────────────────────────\n"

# Checked
./comparator4.sh tests4/empty_file tests4/empty_file > /dev/null 2>&1
check "1" "Both files are empty."

# Checked
./comparator4.sh tests4/file1.txt tests4/file2.txt > /dev/null 2>&1
check "1" "Files are equal and don't contain float numbers."

# Checked
./comparator4.sh tests4/file3.txt tests4/file3.txt > /dev/null 2>&1
check "1" "Files are equal and don't contain float numbers, but contain integers.\n" \
		  "Case with ',' instead of '.' is also checked here."

# Checked
./comparator4.sh tests4/file4.txt tests4/file5.txt > /dev/null 2>&1
check "0" "Files are different and contain equal float numbers, integers should\n" \
		  "be ignored."

# Checked
./comparator4.sh tests4/file6.txt tests4/file7.txt > /dev/null 2>&1
check "0" "Files are different and contain equal float numbers, integers and\n" \
		  "numbers in the words should be ignored."

# Checked
./comparator4.sh tests4/file8.txt tests4/file9.txt > /dev/null 2>&1
check "0" "Files contain equal float numbers and numbers in scientific notation,\n" \
		  "integers and numbers in the words should be ignored."

# Checked
./comparator4.sh tests4/file9.txt tests4/file10.txt > /dev/null 2>&1
check "1" "Files contain equal float numbers and numbers in scientific notation\n" \
		  "with different number of zeros in the end."

# Checked
./comparator4.sh tests4/file9.txt tests4/file13.txt > /dev/null 2>&1
check "1" "Files contain different float numbers and numbers in scientific notation."

# Checked
./comparator4.sh tests4/file11.txt tests4/file12.txt > /dev/null 2>&1
check "1" "Files contain float numbers and numbers in scientific notation with\n" \
		  "leading zeros."


IFS=","
echo -e "\n─────────────────────────────── IFS is not a space ───────────────────────────────\n"

# Checked
./comparator4.sh tests4/empty_file tests4/empty_file > /dev/null 2>&1
check "1" "Both files are empty."

# Checked
./comparator4.sh tests4/file1.txt tests4/file2.txt > /dev/null 2>&1
check "1" "Files are equal and don't contain float numbers."

# Checked
./comparator4.sh tests4/file3.txt tests4/file3.txt > /dev/null 2>&1
check "1" "Files are equal and don't contain float numbers, but contain integers.\n" \
		  "Case with ',' instead of '.' is also checked here."

# Checked
./comparator4.sh tests4/file4.txt tests4/file5.txt > /dev/null 2>&1
check "0" "Files are different and contain equal float numbers, integers should\n" \
		  "be ignored."

# Checked
./comparator4.sh tests4/file6.txt tests4/file7.txt > /dev/null 2>&1
check "0" "Files are different and contain equal float numbers, integers and\n" \
		  "numbers in the words should be ignored."

# Checked
./comparator4.sh tests4/file8.txt tests4/file9.txt > /dev/null 2>&1
check "0" "Files contain equal float numbers and numbers in scientific notation,\n" \
		  "integers and numbers in the words should be ignored."

# Checked
./comparator4.sh tests4/file9.txt tests4/file10.txt > /dev/null 2>&1
check "1" "Files contain equal float numbers and numbers in scientific notation\n" \
		  "with different number of zeros in the end."

# Checked
./comparator4.sh tests4/file9.txt tests4/file13.txt > /dev/null 2>&1
check "1" "Files contain different float numbers and numbers in scientific notation."

# Checked
./comparator4.sh tests4/file11.txt tests4/file12.txt > /dev/null 2>&1
check "1" "Files contain float numbers and numbers in scientific notation with\n" \
		  "leading zeros."


IFS=$old_IFS

echo -e "\n───────────────────────────── All tests have been run ────────────────────────────" \
		"\n──────────────────────────────────── Good luck! ──────────────────────────────────"
