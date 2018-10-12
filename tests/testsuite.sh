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
    printf "RUNNING COMMAND : \"$binary %s\"\n" "$2"
    printf "RESULT : \e[92mOK\e[0m\n\n"
    if [[ "$show_my_res" =~ ^[y]+ ]]; then
        printf "STUDENT'S RESULT :\n$1\n\n"
    fi
}

failure() {
    printf "RUNNING COMMAND : \"$binary %s\"\n" "$3"
    printf "RESULT : \e[91mBAD\e[0m\n\n"
    printf "STUDENT'S RESULT :\n\n$1\n\n"
    printf "SHOULD BE :\n\n$2\n\n"
}

while IFS='' read -a command; do
    altcmd=0
    if [[ "$command" =~ .*-d.* ]]; then
        altcommand=${command/-d}
        altcommand="$altcommand"" -depth"
	my_res=$("$binary" $command)
	res=$(find $altcommand)
    else
	my_res=$("$binary" $command)
	res=$(find $command)
    fi
    if test "$my_res" == "$res"; then
	success "$my_res" "$command"
    else
        failure "$my_res" "$res" "$command"
    fi
done < "$testfile"