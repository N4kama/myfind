CC = gcc
CFLAGS = -g -std=c99 -pedantic -Werror -Wall -Wextra -D_DEFAULT_SOURCE

RES = myfind
SRC = src/string.c src/tree.c src/find.c src/main.c

all:
	$(CC) $(CFLAGS) $(SRC) -o $(RES)

check: all
	./tests/testsuite.sh

clean:
	rm $(RES)