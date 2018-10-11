#include "find.h"

void fill_functions(struct function *function)
{
    //FIX ME WITH FUNC.C FILE
    function[0].name = print;
    //function[0].func = expr_print;
    
    function[1].name = name;
    //function[1].func = expr_name;
}

void path_iter(char *argv[], unsigned int start_index,
               struct options *opt, struct tree *expr)
{
    if (is_expression(argv[start_index]))
    {
        find(".", opt, expr);
    }
    else
    {
        for (; !is_expression(argv[start_index]); start_index++)
        {
            find(argv[start_index], opt, expr);
        }
    }
}

int main(int argc, char *argv[])
{
    if (!argc)
    {
        return 0;
    }
    unsigned int path_start = 1;
    
    struct function functions[NBR_FUNC];
    fill_functions(functions); //NEED TO CREATE FUNC.C WITH THE FUNCTION IMPLEM
    
    struct options opt = fill_options(argv, &path_start, functions);
    if (opt.return_value)
    {
        warnx("cannot do <check options>: The option given doesn't exist %s",
              opt.fail_option);
        return 1;
    }
    
    unsigned int expr_start = expr_find_index(argv, path_start);
    struct tree *expr = setup_tree(functions, argv, expr_start);
    
    path_iter(argv, path_start, &opt, expr);
    
    return opt.return_value;
}