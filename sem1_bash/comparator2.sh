#!/bin/bash

# $1 stores file1
# $2 stores file2
# $3 stores verbose key

error_check(){
	local valid_command="Valid command is: comparator2.sh file_name1 file_name2 [-v]"

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


file_cutter() {
	local search_status=0
	file_cutted=""

	for word in `cat $1`; do
		if [ $search_status -eq 1 ]; then
			file_cutted+="$word "
		elif [ "$word" == "string:" ]; then
			if [ "$2" == "-v" -o "$2" == "--verbose" ]; then
				echo "[+]'string:' word was found in the file $1" $'\n'
			fi 

			search_status=1
		fi
	done

	if [ "$2" == "-v" -o "$2" == "--verbose" ]; then
		if [ $search_status -eq 0 ]; then
			echo "[-]There is no 'string:' word in the file $1" $'\n'
		fi
	fi
}


error_check "$1" "$2" "$3"

file_cutted=""

file_cutter "$1" "$3"
file1_cutted=$file_cutted

file_cutter "$2" "$3"
file2_cutted=$file_cutted


if [ "$file1_cutted" == "$file2_cutted" ]; then
	if [ "$3" == "-v" -o "$3" == "--verbose" ]; then
		echo "[+]Texts after 'string:' in given files are equal."
	fi 

	exit 0
else
	if [ "$3" == "-v" -o "$3" == "--verbose" ]; then
		echo "[-]Texts after 'string:' in given files are NOT equal."
	fi

	exit 1
fi

