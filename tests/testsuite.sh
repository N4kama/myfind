#!/bin/sh

testfile=tests/commands

success() {
    printf "RUNNING COMMAND : \"myfind %s\"\n\n" "$2"
    printf "RESULT : \e[92mOK\e[0m\n\n"
    printf "STUDENT'S RESULT :\n$(cat $1)\n"
}

failure() {
    printf "RUNNING COMMAND : \"myfind %s\"\n\n" "$3"
    printf "RESULT : \e[91mBAD\e[0m\n\n"
    printf "STUDENT'S RESULT :\n\n%s\n\n" "$(cat $1)"
    printf "SHOULD BE :\n\n%s\n\n" "$(cat $2)"
}

while IFS='' read -r command; do
    echo "------->>>>> $command"
    my_res=$(./myfind "$command" > file1)
    res=$(find "$command" > file2)
    the_diff=$(diff file1 file2)
    if [ "$?" -eq 0 ]; then
	success file1 "$command"
    else
	failure file1 file2 "$command"
    fi
done < "$testfile"

if [ -e file1 ] && [ -e file2 ]; then
    rm file1 file2
fi