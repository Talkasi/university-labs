#!/bin/bash

# Задание:
# Сравнивается текст в файлах после первого вхождения подстроки
# «string:». Подразумевается строгое сравнение с учётом разницы в
# пробельных символах и символах окончания строки.

# $1 stores file1
# $2 stores file2
# $3 stores verbose key


error_check(){
	local valid_command="Valid command is: comparator2.sh file_name1 file_name2 [-v]"

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


file_cutter() {
	local search_status=0
	file_cutted=""

	old_IFS=$IFS
	IFS=""

	DONE=false
	until $DONE; do
		read -r line || DONE=true
		# printf "'%s'\n" $line
	    if [ $search_status -eq 0 ]; then
	        if echo "$line" | grep -Eq "string:"; then
	            search_status=1
	            file_cutted="$(echo "$line" | grep -Eo "string:.*")"
	            #printf "'%s'\n" $file_cutted
	        fi
	    else
	        file_cutted="$file_cutted$line\n"
	    fi
	done < "$1"

	IFS=$old_IFS
	#printf "'%s'\n" "$file_cutted"

	if [ $search_status -eq 0 ]; then
		echo -e "[!]Error. There is no 'string:' in the file $1\n" >&2
		exit 1
	fi
}

error_check "$1" "$2" "$3" "$4"

file_cutted=""

file_cutter "$1" "$3"
file1_cutted="$file_cutted"

file_cutter "$2" "$3"
file2_cutted="$file_cutted"

# printf "'%s'\n'%s'\n" "$file1_cutted" "$file2_cutted"
if [ "$file1_cutted" == "$file2_cutted" ]; then
	if [ "$3" == "-v" ] || [ "$3" == "--verbose" ]; then
		echo '[+]Texts after first "string:" in given files are equal.'
	fi 

	exit 0
else
	if [ "$3" == "-v" ] || [ "$3" == "--verbose" ]; then
		echo '[-]Texts after first "string:" in given files are NOT equal.'
	fi

	exit 1
fi
