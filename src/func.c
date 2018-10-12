#include <fnmatch.h>
#include "find.h"

unsigned int expr_name(char *path, char *name_pattern)
{
    //BULLSHIT
    if (path || name_pattern)
	return 1;
    return 1;
}

unsigned int expr_type(char *path, char *type)
{
    //BULLSHIT
    if (path || type)
	return 1;
    return 1;
}