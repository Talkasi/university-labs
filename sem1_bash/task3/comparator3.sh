#!/bin/bash


# Задание:
# Сравниваются последовательности чисел с плавающей точкой (ЧПТ), записанных 
# не в экспоненциальной форме. Каждое найденное ЧПТ заведомо входит в диапазон чисел 
# двойной точности. В файле могут находиться не только числа, но вычленять и анализировать 
# нужно именно их. Сравниваются числа как текст — например, числа 1.0 и 1.00 следует считать различными.


# $1 stores file1
# $2 stores file2
# $3 stores verbose key


error_check(){
	local valid_command="Valid command is: comparator3.sh file_name1 file_name2 [-v]"

	if [ ! -f "$1" ]; then
		echo -e "[!]Error. First parameter is not a file or this file doesn't exist.\n" >&2
		echo "$valid_command" >&2

		exit 1
	elif [ ! -f "$2" ]; then
		echo -e "[!]Error. Second parameter is not a file or this file doesn't exist.\n" >&2
		echo "$valid_command" >&2

		exit 1
	elif [ ! -r "$1" ]; then
		echo -e "[!]Error. There is no permission to open the first file.\n" >&2

		exit 1
	elif [ ! -r "$2" ]; then 
		echo -e "[!]Error. There is no permission to open the second file.\n" >&2

		exit 1
	elif [ ! \( "$3" == "-v" -o "$3" == "--verbose" -o -z "$3" \) ]; then
		echo -e "[!]Error. The key parameter is wrong.\n" >&2
		echo "$valid_command" >&2

		exit 1
	elif [ -n "$4" ]; then
		echo -e "[!]Error. Unexpected parameter after --verbose key.\n" >&2
		echo "$valid_command" >&2

		exit 1
	fi
}


numbers_searcher() {
	old_IFS=$IFS
	IFS=" "

	numbers_line=""

	for word in $(cat "$1"); do
		number=$(echo "$word" | grep -E '^[+-]?[0-9][0-9]*\.[0-9][0-9]*$')
		
		if [ -n "$number" ]; then
			numbers_line+="$number "
		fi
	done

	IFS=$old_IFS

	if [ -z "$numbers_line" ]; then 
		echo "[!]Error. There is no suitable floating point numbers in file '$1'" >&2

		exit 1
	fi
}


error_check "$1" "$2" "$3"

numbers_line=""

numbers_searcher "$1" "$3"
file1_numbers=$numbers_line

numbers_searcher "$2" "$3"
file2_numbers=$numbers_line

numbers_in_files_info="Numbers in file1: $file1_numbers\nNumbers in file2: $file2_numbers"
echo -e "$numbers_in_files_info"

if [ "$file1_numbers" == "$file2_numbers" ]; then
	if [ "$3" == "-v" ] || [ "$3" == "--verbose" ]; then
		echo "[+]Corresponding numbers in given files are equal."
	fi 

	exit 0
else
	if [ "$3" == "-v" ] || [ "$3" == "--verbose" ]; then
		echo "[-]Corresponding numbers in given files are NOT equal."
	fi

	exit 1
fi
