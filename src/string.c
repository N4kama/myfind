#include "find.h"

size_t my_strlen(char *s)
{
    size_t r = 0;
    while (s[r])
    {
	r++;
    }
    return r;
}

void my_path_concat(char *dst, char *path, char *new)
{
    size_t i = 0;
    size_t j = 0;
    for (; path[i]; i++)
    {
	dst[i] = path[i];
    }
    if (dst[i - 1] != '/')
    {
	dst[i] = '/';
	i++;
    }
    for (; new[j]; j++)
    {
	dst[i + j] = new[j];
    }
    dst[i + j] = '\0';
}