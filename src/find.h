#ifndef FIND_H
# define FIND_H

#define NBR_FUNC 2

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <err.h>

#include "string.h"

enum symlinks
{
    P = 0,
    H,
    L
};

enum operator
{
    AND,
    OR
};

enum func_name
{
    print,
    name
};

enum mode
{
    OPERATOR,
    FUNC
};

struct options
{
    int return_value;
    int depth;
    enum symlinks symlinks;
    char *fail_option;
};

struct function
{
    enum func_name name;
    int (*func)(char *path, struct options *opt);
};

struct tree
{
    enum mode mode;
    enum operator operator;
    struct function func;
    struct tree *lson;
    struct tree *rson;
};

unsigned int is_expr_detailed(char *s, struct function *functions);
unsigned int is_expression(char *s);
unsigned int expr_find_index(char *argv[], unsigned int start);
unsigned int check_options(struct options *opt, char *option,
			   struct function *functions);
struct options fill_options(char *argv[], unsigned int *start,
			    struct function *functions);

unsigned int is_dir(char *path, struct options *opt);
void find(char *path, struct options *opt, struct tree *expr);

#endif /* !FIND_H */