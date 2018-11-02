#ifndef FIND_H
#define FIND_H

#define NBR_FUNC 5

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <err.h>
#include <sys/wait.h>

#include "string.h"

enum symlinks
{
    P = 0,
    H,
    L
};

enum operator
{
    AND = 0,
    OR
};

enum mode
{
    OPERATOR,
    FUNC
};

struct function
{
    char *name;
    unsigned int (*func)();
    char **argv;
};

struct options
{
    int return_value;
    int depth;
    enum symlinks symlinks;
    struct function *functions;
    char *fail_option;
};

struct tree
{
    enum mode mode;
    enum operator operator;
    struct function func;
    struct tree *lson;
    struct tree *rson;
};

struct stack
{
    struct tree *root;
    struct stack *next;
};

struct stacks
{
    struct stack *op;
    struct stack *func;
};

int is_operator(char *s);
int is_func_expr(char *s, struct function *functions);
unsigned int is_test_func(char *s);
unsigned int is_action_func(char *s);
unsigned int is_expr_detailed(char *s, struct function *functions);
unsigned int is_expression(char *s);
unsigned int expr_find_index(char *argv[], unsigned int start);
unsigned int check_options(struct options *opt, char *option);
struct options fill_options(char *argv[], unsigned int *start,
                            struct function *functions);

unsigned int expr_name();
unsigned int expr_type();
unsigned int expr_print(char *path);
unsigned int expr_exec();
unsigned int expr_execdir();

struct tree *setup_tree(struct function *functions, char *argv[], int start);
void destroy_tree(struct tree *root);

unsigned int is_dir(char *path, struct options *opt);
void find(char *path, struct options *opt, struct tree *expr);

#endif /* !FIND_H */