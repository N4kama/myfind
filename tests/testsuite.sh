#!/bin/sh

OK="\e[92mOK\e[0m"
BAD="\e[91mBAD\e[0m"

success() {
    printf "RUNNING COMMAND : \"myfind %s\"\n\n" "$2"
    printf "RESULT : %s\n\n" "$OK"
    printf "STUDENT'S RESULT :\n%s\n" "$1"
}

failure() {
    printf "RUNNING COMMAND : \"myfind %s\"\n\n" "$3"
    printf "RESULT : %s\n\n" "$BAD"
    printf "STUDENT'S RESULT :\n%s\n" "$1"
    printf "SHOULD BE :\n%s\n" "$2"
}

while IFS='' read -r command; do
    my_res=$(./../myfind "$command")
    res=$(find "$command")
    diff my_res res
    if [ "$?" -eq 0 ]; then
	success my_res command
    else
	failure my_res res command
    fi
done < commands