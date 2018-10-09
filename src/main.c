#include "find.h"

//FUNC -> fill options struct with the args ?

//FILL the paths list

//FUNC -> validity args ?

int main(int argc, char *argv[])
{
    if (argc == 1)
	find(".");
    else
	find(argv[1]);
}
