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

unsigned int expr_type(char *path, char *type_arg)
{
    char type = type_arg[0];
    struct stat st;
    if (lstat(path, &st))
    {
        return 0;
    }
    switch (type)
    {
    case 'b':
        return S_ISBLK(st.st_mode);
    case 'c':
        return S_ISCHR(st.st_mode);
    case 'd':
        return S_ISDIR(st.st_mode);
    case 'f':
        return S_ISREG(st.st_mode);
    case 'l':
        return S_ISLNK(st.st_mode);
    case 'p':
        return S_ISFIFO(st.st_mode);
    case 's':
        return S_ISSOCK(st.st_mode);
    default:
        return 0;
    }
    return 0;
}

unsigned int expr_print(char *path)
{
    printf("%s\n", path);
    return 1;
}

unsigned int expr_exec(char *argv[], int *tab)
{
    pid_t pid;
    int status;
    if (!(pid = fork()))
    {
        execvp(argv[0], argv);
    }
    while (waitpid(pid, &status, 0) == pid)
    {
        continue;
    }
    replace_path(argv, tab);
    if (!WEXITSTATUS(status))
    {
        return 1;
    }
    return 0;
}

unsigned int expr_execdir(char *pathh, char *name, char *argv[])
{
    size_t len = my_strlen(pathh) - 1;
    char *path = malloc((len + 1) * sizeof(char));
    my_strcpy(path, pathh);
    len--;
    for (; path[len] && path[len] != '/'; len--)
    {
        continue;
    }
    if (path[len])
    {
        path[len] = '\0';
        chdir(path);
    }
    char *new = malloc((my_strlen(name) + 2) * sizeof(char));
    new[0] = '.';
    new[1] = '/';
    my_strcpy(new + 2, name);
    int *tab = replace_with_path(new, argv);
    unsigned int r = expr_exec(argv, tab);
    free(new);
    if (path[len])
    {
        chdir(pathh);
    }
    free(path);
    return r;
}