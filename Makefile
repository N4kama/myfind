CC = gcc
CFLAGS = -g std=c99 -pedantic -Werror -Wall -Wextra

RES = myfind
SRC = main.c

all:
	$(CC) $(CFLAGS) $(SRC) -o $(RES)

test: all
	./tests/testsuite.sh

clean:
	rm $(RES)