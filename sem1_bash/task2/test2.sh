#!/bin/bash
echo "────────────── Welcome to the validation tool of the comparator #2! ──────────────"


check() {
	command="$(echo $?)"
	[ $command == "$1" ] && echo -e "[PASSED] $2$3" || echo -e \
	"\n[FAILED] $2$3\n> Expected $1, but $command got.\n"
}


echo -e "─────────── Testing the comparator for errors in the given parameters ────────────\n"

./comparator2.sh > /dev/null 2>&1
check "1" "No parameters are passed."

./comparator2.sh tests2/file1.txt --verbose > /dev/null 2>&1
check "1" "One of the files is not specified. Key --verbose is specified."

./comparator2.sh tests2/file1.txt > /dev/null 2>&1
check "1" "One of the files is not specified. Key --verbose is not specified too."

./comparator2.sh tests2/not_exist.txt tests2/file1.txt > /dev/null 2>&1
check "1" "The first file does not exist."

./comparator2.sh tests2/file1.txt tests2/not_exist.txt > /dev/null 2>&1
check "1" "The second file does not exist."

./comparator2.sh tests2/not_readable.txt tests2/file1.txt > /dev/null 2>&1
check "1" "No permissions to read the first file."

./comparator2.sh tests2/file1.txt tests2/not_readable.txt > /dev/null 2>&1
check "1" "No permissions to read the second file."

./comparator2.sh tests2/file1.txt tests2/file1.txt -va > /dev/null 2>&1
check "1" "Key parameter is wrong."

./comparator2.sh tests2/file1.txt tests2/file1.txt --verbose smthing else > /dev/null 2>&1
check "1" "More parameters are being passed than needed."

old_IFS=$IFS 
IFS=" "

echo -e "\n────────────────────────── The main comparator #2 tests ──────────────────────────"
echo -e "────────────────────────────────── IFS is a space ────────────────────────────────\n"

# Checked
./comparator2.sh tests2/empty_file tests2/empty_file > /dev/null 2>&1
check "1" "Both files are empty."

# Checked
./comparator2.sh tests2/file1.txt tests2/file1.txt > /dev/null 2>&1
check "1" "Files are equal and don't contain a substring \"string:\"."

# Checked
./comparator2.sh tests2/file1.txt tests2/file3.txt > /dev/null 2>&1
check "1" "Files are not equal and don't contain a substring \"string:\"."

# Checked
./comparator2.sh tests2/file5.txt tests2/file5.txt > /dev/null 2>&1
check "0" "Files are equal and contain a substring \"string:\" in the beginning."

# Checked
./comparator2.sh tests2/file6.txt tests2/file6.txt > /dev/null 2>&1
check "0" "Files are equal and contain a substring \"string:\" in the end."

# Checked
./comparator2.sh tests2/file4.txt tests2/file4.txt > /dev/null 2>&1
check "0" "Files are equal and contain a substring \"string:\" in the middle."

# Checked
./comparator2.sh tests2/file4.txt tests2/file7.txt > /dev/null 2>&1
check "0" "Files are not equal before a substring \"string:\" and equal after it.\n" \
		  "Each word is separated from it's neighbors by 1 space character."

# Checked
./comparator2.sh tests2/file8.txt tests2/file9.txt > /dev/null 2>&1
check "0" "Files are not equal before a substring \"string:\" and equal after it.\n" \
		  "Each word is separated from it's neighbors by several number of space characters."

# Checked
./comparator2.sh tests2/file4.txt tests2/file5.txt > /dev/null 2>&1
check "0" "Substring \"string:\" is in the beginning of a word in the text.\n" \
		  "Files are not equal before a substring \"string:\" and equal after it."

# Checked
./comparator2.sh tests2/file10.txt tests2/file11.txt > /dev/null 2>&1
check "0" "Substring \"string:\" is in the middle of a word in the text.\n" \
		  "Files are not equal before a substring \"string:\" and equal after it."

# Checked
./comparator2.sh tests2/file12.txt tests2/file13.txt > /dev/null 2>&1
check "0" "Substring \"string:\" is in the end of a word in the text."

# Checked
./comparator2.sh tests2/file4.txt tests2/file9.txt > /dev/null 2>&1
check "1" "Files are not equal after a substring \"string:\"."

# Checked
./comparator2.sh tests2/file5.txt tests2/file9.txt > /dev/null 2>&1
check "1" "Files contain several substrings \"string:\" and\n" \
		  "are not equal between first one and second one."

# Checked
./comparator2.sh tests2/file4.txt tests2/file2.txt > /dev/null 2>&1
check "1" "Files contain substring \"string:\" and are equal before the last symbol:\n" \
		  "one file has new line in the end."

# Checked
./comparator2.sh tests2/file1 tests2/file2 > /dev/null 2>&1
check "1" "Files contain substring \"string:\" and are equal before spaces in the end:\n" \
		  "the first file has few spaces, while the second don't."

IFS=","
echo -e "\n─────────────────────────────── IFS is not a space ───────────────────────────────\n"

# Checked
./comparator2.sh tests2/empty_file tests2/empty_file > /dev/null 2>&1
check "1" "Both files are empty."

# Checked
./comparator2.sh tests2/file1.txt tests2/file1.txt > /dev/null 2>&1
check "1" "Files are equal and don't contain a substring \"string:\"."

# Checked
./comparator2.sh tests2/file1.txt tests2/file3.txt > /dev/null 2>&1
check "1" "Files are not equal and don't contain a substring \"string:\"."

# Checked
./comparator2.sh tests2/file5.txt tests2/file5.txt > /dev/null 2>&1
check "0" "Files are equal and contain a substring \"string:\" in the beginning."

# Checked
./comparator2.sh tests2/file6.txt tests2/file6.txt > /dev/null 2>&1
check "0" "Files are equal and contain a substring \"string:\" in the end."

# Checked
./comparator2.sh tests2/file4.txt tests2/file4.txt > /dev/null 2>&1
check "0" "Files are equal and contain a substring \"string:\" in the middle."

# Checked
./comparator2.sh tests2/file4.txt tests2/file7.txt > /dev/null 2>&1
check "0" "Files are not equal before a substring \"string:\" and equal after it.\n" \
		  "Each word is separated from it's neighbors by 1 space character."

# Checked
./comparator2.sh tests2/file8.txt tests2/file9.txt > /dev/null 2>&1
check "0" "Files are not equal before a substring \"string:\" and equal after it.\n" \
		  "Each word is separated from it's neighbors by several number of space characters."

# Checked
./comparator2.sh tests2/file4.txt tests2/file5.txt > /dev/null 2>&1
check "0" "Substring \"string:\" is in the beginning of a word in the text.\n" \
		  "Files are not equal before a substring \"string:\" and equal after it."

# Checked
./comparator2.sh tests2/file10.txt tests2/file11.txt > /dev/null 2>&1
check "0" "Substring \"string:\" is in the middle of a word in the text.\n" \
		  "Files are not equal before a substring \"string:\" and equal after it."

# Checked
./comparator2.sh tests2/file12.txt tests2/file13.txt > /dev/null 2>&1
check "0" "Substring \"string:\" is in the end of a word in the text."

# Checked
./comparator2.sh tests2/file4.txt tests2/file9.txt > /dev/null 2>&1
check "1" "Files are not equal after a substring \"string:\"."

# Checked
./comparator2.sh tests2/file5.txt tests2/file9.txt > /dev/null 2>&1
check "1" "Files contain several substrings \"string:\" and\n" \
		  "not equal between first one and second one."

# Checked
./comparator2.sh tests2/file4.txt tests2/file2.txt > /dev/null 2>&1
check "1" "Files contain substring \"string:\" and are equal before the last symbol:\n" \
		  "one file has new line in the end."

# Checked
./comparator2.sh tests2/file1 tests2/file2 > /dev/null 2>&1
check "1" "Files contain substring \"string:\" and are equal before spaces in the end:\n" \
		  "the first file has few spaces, while the second don't."

IFS=$old_IFS

echo -e "\n───────────────────────────── All tests have been run ────────────────────────────" \
		"\n──────────────────────────────────── Good luck! ──────────────────────────────────"
