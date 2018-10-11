#include "find.h"

unsigned int is_dir(char *path, struct options *opt)
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

static unsigned int exec_func(char *path, struct function func)
{
    if (my_strcmp(func.name, "expr_name"))
    {
	return func.func(path, func.argv[0]);
    }
    if (my_strcmp(func.name, "expr_type"))
    {
	return func.func(path, func.argv[0]);
    }
    return 0;
}

static unsigned int expr_treatment_rec(char *path, struct tree *expr)
{
    if (expr->mode == OPERATOR)
    {
        switch (expr->operator)
        {
        case AND:
            if (expr_treatment_rec(path, expr->lson))
            {
                return expr_treatment_rec(path, expr->rson);
            }
            return 0;
            break;
        case OR:
            if (expr_treatment_rec(path, expr->lson))
            {
                return 1;
            }
            return expr_treatment_rec(path, expr->rson);
            break;
        default:
            return 0;
        }
    }
    else
    {
        if(exec_func(path, expr->func))
	{
	    printf("%s\n", path);
	    return 1;
	}
	return 0;
    }
}

static void expr_treatment(char *path, struct tree *expr)
{
    //IF EXPR IS NULL, THEN THERE IS NO EXPR, SO IT JUST PRINTS
    if (!expr)
    {
        printf("%s\n", path);
    }
    else
    {
        expr_treatment_rec(path, expr);
    }
}

static void find_default(char path[], struct options *opt, struct tree *expr)
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
            expr_treatment(new, expr);
            find_default(new, opt, expr);
            free(new);
        }
    }
    closedir(dir);
}

static void find_post_order(char path[], struct options *opt, struct tree *expr)
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
            find_post_order(new, opt, expr);
            expr_treatment(new, expr);
            free(new);
        }
    }
    closedir(dir);
}

void find(char *path, struct options *opt, struct tree *expr)
{
    if (opt->depth)
    {
        find_post_order(path, opt, expr);
        expr_treatment(path, expr);
    }
    else
    {
        expr_treatment(path, expr);
        find_default(path, opt, expr);
    }
} //NEED TO CREATE FUNC.C WITH THE FUNCTION IMPLEM