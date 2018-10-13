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

unsigned int my_strcmp(char *a, char *b)
{
    while (*a && *b && (*a == *b))
    {
        a++;
        b++;
    }
    if (!a || !b || (*a != *b))
        return 0;
    return 1;
}

void my_strcpy(char *dst, char *src)
{
    for (size_t i = 0; src[i]; i++)
    {
        dst[i] = src[i];
    }
}

void fill_str_cmd(char *argv[], unsigned int *start, char ***new)
{
    int count = 0;
    for (; argv[*start] && argv[*start][0] != ';'; *start += 1, count++)
    {
        continue;
    }
    *new = malloc((count + 1) * sizeof(char *));
    (*new)[count] = NULL;
    int save = count;
    count--;
    for (; count >= 0; count--)
    {
        (*new)[count] = argv[*start - save + count];
    }
}

int *replace_with_path(char *path, char *argv[])
{
    int *tab = calloc(256, sizeof(int));
    for (int i = 0; argv[i]; i++)
    {
        if (my_strcmp(argv[i], "{}"))
        {
            argv[i] = path;
            tab[i] = 1;
        }
    }
    return tab;
}

void replace_path(char *s[], int *arr)
{
    for (int i = 0; i < 256; i++)
    {
        if (arr[i])
        {
            s[i] = "{}";
        }
    }
    free(arr);
}