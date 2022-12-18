#!/bin/bash


# Задание:
# Сравниваются последовательности чисел с плавающей точкой (ЧПТ),
# записанных в том числе в экспоненциальной форме. Каждое найденное
# ЧПТ заведомо входит в диапазон чисел двойной точности. Обращаем
# Ваше внимание, что в файле могут находиться не только числа, но вычленять и 
# анализировать нужно именно их. Сравниваются числа как текст — например, 
# числа 1.0 и 1.00 следует считать различными, числа 1.0 и 1.0e0 – тоже.


# $1 stores file1
# $2 stores file2
# $3 stores verbose key


error_check(){
	local valid_command="Valid command is: comparator2.sh file_name1 file_name2 [-v]"

	if [ ! \( "$3" == "-v" -o "$3" == "--verbose" -o -z "$3" \) ]; then
		echo "[!]Error. The key parameter is wrong." >&2
		echo $valid_command >&2

		exit 1
	elif [ ! -f "$1" ]; then
		echo "[!]Error. First parameter is not a file." >&2
		echo $valid_command >&2

		exit 1
	elif [ ! -f "$2" ]; then
		echo "[!]Error. Second parameter is not a file." >&2
		echo $valid_command >&2

		exit 1
	fi
}


numbers_searcher() {
	numbers_line=""
	old_IFS=$IFS
	IFS=" "

	for word in `cat $1`; do
		number="$(echo "$word" | grep -E '^[+-]?[0-9][0-9]*\.[0-9][0-9]*$')"
		number+="$(echo "$word" | grep -E '^[+-]?[0-9][0-9]*\.[0-9][0-9]*[eE][+-]?[0-9][0-9]*$')"
		number+="$(echo "$word" | grep -E '^[+-]?[0-9][0-9]*[eE][+-]?[0-9][0-9]*$')"

		if [ -n "$number" ]; then
			numbers_line="$numbers_line$number "
		fi
	done

	IFS=$old_IFS

	if [ -z "$numbers_line" ]; then 
		echo "[!]Error. There is no suitable floating point numbers in the file '$1'" >&2
		
		exit 1
	fi
}


error_check "$1" "$2" "$3"

numbers_line=""

numbers_searcher $1 $3
file1_numbers="$numbers_line"

numbers_searcher $2 $3
file2_numbers="$numbers_line"

numbers_in_files_info="Numbers in file1: $file1_numbers\nNumbers in file2: $file2_numbers"
echo -e $numbers_in_files_info

if [ "$file1_numbers" == "$file2_numbers" ]; then
	if [ "$3" == "-v" -o "$3" == "--verbose" ]; then
		echo "[+]Corresponding numbers in given files are equal."
	fi 

	exit 0
else
	if [ "$3" == "-v" -o "$3" == "--verbose" ]; then
		echo "[-]Corresponding numbers in given files are NOT equal."
	fi

	exit 1
fi
