CC = gcc
CFLAGS = -g -std=c99 -pedantic -Werror -Wall -Wextra -D_DEFAULT_SOURCE

RES = myfind
SRC = src/tree_stack.c src/func.c src/opt_expr.c \
src/string.c src/find.c src/main.c

all:
	$(CC) $(CFLAGS) $(SRC) -o $(RES)

check: all
	./tests/testsuite.sh

clean:
	rm $(RES)