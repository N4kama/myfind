#include "find.h"

int is_dir(char *path, struct options *opt)
{
    struct stat st;
    if (lstat(path, &st))
    {
        warnx("cannot do stat: Error while with stats of file : %s", path);
        opt->return_value = 1;
    }
    if (S_ISDIR(st.st_mode) || (S_ISLNK(st.st_mode) && (opt->symlinks == L ||
                                                        opt->symlinks == H)))
    {
        if (opt->symlinks == H)
        {
            opt->symlinks = P;
        }
        return 1;
    }
    return 0;
}

static void check_error_dir(char path[], struct options *opt)
{
    warnx("cannot do opendir: ‘%s’ --> No such file or directory",
          path);
    opt->return_value = 1;
}

static void find_default(char path[], struct options *opt)
{
    if (!is_dir(path, opt))
    {
        return;
    }
    DIR *dir = opendir(path);
    if (!dir)
    {
        check_error_dir(path, opt);
    }
    else
    {
        struct dirent *cur = readdir(dir);
        readdir(dir);
        for (cur = readdir(dir); cur; cur = readdir(dir))
        {
            size_t len = my_strlen(path) + my_strlen(cur->d_name) + 2;
            char *new = malloc(len * sizeof(char));
            my_path_concat(new, path, cur->d_name);
            printf("%s\n", new);
            find_default(new, opt);
            free(new);
        }
    }
    closedir(dir);
}

static void find_post_order(char path[], struct options *opt)
{
    if (!is_dir(path, opt))
    {
        return;
    }
    DIR *dir = opendir(path);
    if (!dir)
    {
        check_error_dir(path, opt);
    }
    else
    {
        struct dirent *cur = readdir(dir);
        readdir(dir);
        for (cur = readdir(dir); cur; cur = readdir(dir))
        {
            size_t len = my_strlen(path) + my_strlen(cur->d_name) + 2;
            char *new = malloc(len * sizeof(char));
            my_path_concat(new, path, cur->d_name);
            find_post_order(new, opt);
            printf("%s\n", new);
            free(new);
        }
    }
    closedir(dir);
}

void find(char *path, struct options *opt)
{
    if (opt->depth)
    {
        find_post_order(path, opt);
        printf("%s\n", path);
    }
    else
    {
        printf("%s\n", path);
        find_default(path, opt);
    }
}