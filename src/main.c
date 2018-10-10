#include "find.h"

int check_options(struct options *opt, char *option)
{
    if (option[0] != '-')
    {
        return 0;
    }
    switch (option[1])
    {
    case 'd':
        opt->depth = 1;
        break;
    case 'H':
        opt->symlinks = H;
        break;
    case 'L':
        opt->symlinks = L;
        break;
    case 'P':
        opt->symlinks = P;
        break;
    default:
        opt->fail_option = option;
        opt->return_value = 1;
        return 0;
    }
    return 1;
}

struct options fill_options(char *argv[], int *start)
{
    struct options opt =
        {
            0, 0, 0, NULL
        };
    for (; argv[*start] && check_options(&opt, argv[*start]); *start += 1)
    {
        continue;
    }
    return opt;
}

//FILL the paths list

int main(int argc, char *argv[])
{
    if (!argc)
    {
        return 0;
    }
    int path_start = 1;
    struct options opt = fill_options(argv, &path_start);
    if (opt.return_value)
    {
        warnx("cannot do <check options>: The option given doesn't exist %s",
              opt.fail_option);
        return 1;
    }
    if (!argv[path_start])
    {
        find(".", &opt);
    }
    else
    {
        find(argv[path_start], &opt);
    }
    return opt.return_value;
}