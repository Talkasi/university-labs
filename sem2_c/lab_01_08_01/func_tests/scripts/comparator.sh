#!/bin/bash

# $1 stores file1
# $2 stores file2
# $3 stores verbose key

error_check() {
  local valid_command="Valid command is: comparator.sh file_name1 file_name2 [-v]"

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
  elif [ "$3" != "-v" ] && [ "$3" != "--verbose" ] && [ "$3" != "" ]; then
    echo -e "[!]Error. The key parameter is wrong.\n" >&2
    echo "$valid_command" >&2

    exit 1
  elif [ -n "$4" ]; then
    echo -e "[!]Error. Unexpected parameter after --verbose key.\n" >&2
    echo "$valid_command" >&2

    exit 1
  fi
}

error_check "$1" "$2" "$3" "$4"

old_IFS=$IFS
IFS=""

file1="$(mktemp)"
search_status=0

DONE=false
until $DONE; do
  read -r line || DONE=true
  if [ $search_status -eq 0 ]; then
    if [[ "$line" == *"Result:"* ]]; then
      search_status=1
      new_line="$(echo "$line" | grep -Eo "Result:.*")"
      echo "$new_line" >"$file1"
    fi
  else
    echo "$line" >>"$file1"
  fi
done <"$1"

if [ $search_status -eq 0 ]; then
  rm "$file1"
  echo -e "[!]Error. There is no 'Result:' in the file $1\n" >&2
  IFS=$old_IFS
  exit 1
fi

file2="$(mktemp)"
search_status=0
DONE=false
until $DONE; do
  read -r line || DONE=true
  if [ $search_status -eq 0 ]; then
    if [[ "$line" == *"Result:"* ]]; then
      search_status=1
      new_line="$(echo "$line" | grep -Eo "Result:.*")"
      echo "$new_line" >"$file2"
    fi
  else
    echo "$line" >>"$file2"
  fi
done <"$2"

if [ $search_status -eq 0 ]; then
  rm "$file1" "$file2"
  IFS=$old_IFS

  echo -e "[!]Error. There is no 'Result:' in the file $2\n" >&2
  exit 1
fi

IFS=$old_IFS

if cmp -s "$file1" "$file2"; then
  if [ "$3" == "-v" ] || [ "$3" == "--verbose" ]; then
    echo '[+]Texts after first "Result:" in given files are equal.'
  fi
  rm "$file1" "$file2"

  exit 0
else
  if [ "$3" == "-v" ] || [ "$3" == "--verbose" ]; then
    echo '[-]Texts after first "Result:" in given files are NOT equal.'
  fi
  rm "$file1" "$file2"

  exit 1
fi
