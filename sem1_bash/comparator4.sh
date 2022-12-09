#!/bin/bash

# $1 stores file1
# $2 stores file2
# $3 stores verbose key

error_check(){
	local valid_command="Valid command is: comparator3.sh file_name1 file_name2 [-v]"

	if [ ! \( "$3" == "-v" -o "$3" == "--verbose" -o -z "$3" \) ]; then
		echo "[!]Error.The key is wrong." >&2
		echo $valid_command >&2
		exit 1

	elif [ ! -f "$1" ]; then
		if [ "$3" == "-v" -o "$3" == "--verbose" ]; then
			echo "[!]Error. First parameter is not a file." >&2
			echo $valid_command >&2
		fi

		exit 1

	elif [ ! -f "$2" ]; then
		if [ "$3" == "-v" -o "$3" == "--verbose" ]; then
			echo "[+]'string:' word was found in the file $1" >&2
			echo $valid_command >&2
		fi

		exit 1
	fi
}


numbers_searcher() {
	numbers_line=""

	for word in `cat $1`; do
		if echo "$word" | grep -Eq '[+-]?[0-9].[0-9][0-9]*[eE][+-]?[0-9][0-9]*' ; then
			numbers_line+="$word "
		elif echo "$word" | grep -Eq '[+-]?[0-9][0-9]*.[0-9][0-9]*' ; then
			numbers_line+="$word "
		fi
	done
}


error_check "$1" "$2" "$3"

numbers_line=""

numbers_searcher $1 $3
file1_numbers=$numbers_line
if [ "$3" == "-v" -o "$3" == "--verbose" ]; then
	if [ -z "$file1_numbers" ]; then 
		echo "[-]There is no numbers in file '$1'"
	else
		echo "[+]Numbers were found in file '$1'"
	fi
fi 

numbers_searcher $2 $3
file2_numbers=$numbers_line
if [ "$3" == "-v" -o "$3" == "--verbose" ]; then
	if [ -z "$file2_numbers" ]; then 
		echo "[-]There is no numbers in file '$2'"
	else
		echo "[+]Numbers were found in file '$2'"
	fi
fi 


numbers_in_files_info="Numbers in file1: $file1_numbers $'\n' Numbers in file2: $file2_numbers"

if [ "$file1_numbers" == "$file2_numbers" ]; then
	if [ "$3" == "-v" -o "$3" == "--verbose" ]; then
		echo "[+]Corresponding numbers in given files are equal."
		echo $numbers_in_files_info
	fi 

	exit 0
else
	if [ "$3" == "-v" -o "$3" == "--verbose" ]; then
		echo "[-]Corresponding numbers in given files are NOT equal."
		echo $numbers_in_files_info
	fi

	exit 1
fi
