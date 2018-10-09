#!/bin/sh

printf "Path to binary : "
read binary
printf "Path to commands_file : "
read testfile
printf "Show student's results in case of succes ? (y/n) : "
read show_my_res
echo

success() {
    printf "RUNNING COMMAND : \"$binary %s\"\n\n" "$2"
    printf "RESULT : \e[92mOK\e[0m\n\n"
    if [[ "$show_my_res" =~ ^[y]+ ]]; then
	printf "STUDENT'S RESULT :\n$(cat $1)\n"
    fi
}

failure() {
    printf "RUNNING COMMAND : \"$binary %s\"\n\n" "$3"
    printf "RESULT : \e[91mBAD\e[0m\n\n"
    printf "STUDENT'S RESULT :\n\n$(cat $1)\n\n"
    printf "SHOULD BE :\n\n$(cat $2)\n\n"
}

while IFS='' read -r command; do
    my_res=$("$binary" "$command" > file1)
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