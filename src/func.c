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
    waitpid(pid, &status, WUNTRACED | WCONTINUED);
    replace_path(argv, tab);
    if (!WEXITSTATUS(status))
    {
        return 1;
    }
    return 0;
}

unsigned int expr_execdir(char *path, char *argv[], int *tab)
{
    free(tab);
    if (path || argv || tab)
    {
        return 1;
    }
    return 1;
}