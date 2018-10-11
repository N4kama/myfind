#include "find.h"

unsigned int is_expr_detailed(char *s, struct function *functions)
{
    if (s[0] == '-' || s[0] == '(')
    {
	for (unsigned int i = 0; i < NBR_FUNC; i++)
	{
	    if (my_strcmp(s + 1, functions[i].name))
	    {
		return 1;
	    }
	}
    }
    return 0;
}

unsigned int is_expression(char *s)
{
    if (!s)
    {
	return 0;
    }
    if (s[0] == '-' || s[0] == '(')
    {
	return 1;
    }
    return 0;
}

unsigned int expr_find_index(char *argv[], unsigned int start)
{
    unsigned int r = start;
    for (; argv[r] && !is_expression(argv[r]); r++)
    {
	continue;
    }
    return r;
}

unsigned int check_options(struct options *opt, char *option)
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
	if (is_expr_detailed(option, opt->functions))
	{
	    return 1;
	}
        opt->fail_option = option;
        opt->return_value = 1;
        return 0;
    }
    return 1;
}

struct options fill_options(char *argv[], unsigned int *start,
			    struct function *functions)
{
    struct options opt =
        {
            0, 0, 0, functions, NULL
        };
    for (; argv[*start] && check_options(&opt, argv[*start]);
	 *start += 1)
    {
        continue;
    }
    return opt;
}