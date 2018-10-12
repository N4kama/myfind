#include <fnmatch.h>
#include "find.h"

unsigned int expr_name(char *name, char *name_pattern)
{
    if (!fnmatch(name_pattern, name, 0))
    {
	return 1;
    }
    return 0;
}

unsigned int expr_type(char *path, char *type)
{
    //BULLSHIT
    if (path || type)
	return 1;
    return 1;
}