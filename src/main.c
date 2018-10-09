#include "find.h"

struct options fill_options(void)
{
    struct options opt;
    opt.return_value = 0;
    return opt;
}

//FILL the paths list

//FUNC -> validity args ?

int main(int argc, char *argv[])
{
    struct options opt = fill_options();
    if (argc == 1)
	find(".", &opt);
    else
	find(argv[1], &opt);
    return opt.return_value;
}
