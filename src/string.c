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

void my_path_concat(char *dst, char *path, char *new, size_t len)
{
    size_t i = 0;
    for (; path[i]; i++)
    {
	dst[i] = path[i];
    }
    for (size_t j = 0; j + i < len; j++)
    {
	dst[i + j] = new[j];
    }
}