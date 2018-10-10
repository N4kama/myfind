#!/bin/sh

binary=./myfind
testfile=tests/commands
#printf "Path to binary : "
#read binary
#printf "Path to commands_file : "
#read testfile
printf "Show student's results in case of succes ? (y/n) : "
read show_my_res
echo

success() {
    printf "RUNNING COMMAND : \"$binary %s\"\n\n" "$2"
    printf "RESULT : \e[92mOK\e[0m\n\n"
    if [[ "$show_my_res" =~ ^[y]+ ]]; then
        printf "STUDENT'S RESULT :\n$1\n"
    fi
}

failure() {
    printf "RUNNING COMMAND : \"$binary %s\"\n\n" "$3"
    printf "RESULT : \e[91mBAD\e[0m\n\n"
    printf "STUDENT'S RESULT :\n\n$1\n\n"
    printf "SHOULD BE :\n\n$2\n\n"
}

while IFS='' read -r command; do
    if [ "$command" == "" ]; then
	my_res=$("$binary")
        res=$(find)
    elif [[ "$command" =~ ^-d ]]; then
	new_cmd=$(echo "$command" | cut -d ' ' -f2)
	my_res=$("$binary" -d "$new_cmd")
        res=$(find "$new_cmd" -depth)
    elif [[ "$command" =~ ^-H ]]; then
	new_cmd=$(echo "$command" | cut -d ' ' -f2)
	my_res=$("$binary" -H "$new_cmd")
        res=$(find -H "$new_cmd")
    elif [[ "$command" =~ ^-L ]]; then
	new_cmd=$(echo "$command" | cut -d ' ' -f2)
	my_res=$("$binary" -L "$new_cmd")
        res=$(find -L "$new_cmd")
    elif [[ "$command" =~ ^-P ]]; then
	new_cmd=$(echo "$command" | cut -d ' ' -f2)
	my_res=$("$binary" -P "$new_cmd")
        res=$(find -P "$new_cmd")
    else
	my_res=$("$binary" "$command")
        res=$(find "$command")
    fi
    if test "$my_res" == "$res"; then
	success "$my_res" "$command"
    else
        failure "$my_res res" "$command"
    fi
done < "$testfile"