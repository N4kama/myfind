#include "find.h"

static struct tree *create_tree(enum mode mode, enum operator op,
				struct function func)
{
    struct tree *root = malloc(sizeof(struct tree));
    if (!root)
    {
        return NULL;
    }
    root->mode = mode;
    if (mode == OPERATOR)
    {
        root->operator = op;
    }
    else
    {
        root->func = func;
    }
    root->lson = NULL;
    root->rson = NULL;
    return root;
}

static struct stack *push(struct stack *cur, enum mode mode, enum operator op,
                   struct function func)
{
    struct tree *root = create_tree(mode, op, func);
    if (!root)
    {
        return NULL;
    }
    struct stack *s = malloc(sizeof(struct stack));
    if (!s)
    {
        free(root);
        return NULL;
    }
    s->root = root;
    s->next = cur;
    return s;
}

static struct tree *pop(struct stack *cur)
{
    struct tree *root = cur->root;
    struct stack *tmp = cur->next;
    free(cur);
    cur = tmp;
    return root;
}

static void setup_argv(struct function *func, char *argv[], unsigned int *start,
		       struct function *functions)
{
    if (is_operator(argv[*start]) != -1 ||
	is_func_expr(argv[*start], functions) != -1)
    {
	func->argv = NULL;
	return;
    }
    if (my_strcmp(func->name, "expr_name") ||
	my_strcmp(func->name, "expr_type"))
    {
	func->argv = malloc(sizeof(char *));
	func->argv[0] = argv[*start];
    }
    *start += 1;
}

static void fill_stacks(struct stacks *stacks, char *argv[], unsigned int start,
                        struct function *functions)
{
    int r;
    for (; argv[start];)
    {
        if ((r = is_func_expr(argv[start], functions)) != -1)
        {
            stacks->func = push(stacks->func, FUNC, AND, functions[r]);
            start++;
	    setup_argv(&stacks->func->root->func, argv, &start, functions);
            if (argv[start] && (r = is_func_expr(argv[start], functions)) != -1)
            {
                stacks->func = push(stacks->op, OPERATOR, AND, functions[0]);
                stacks->func = push(stacks->func, FUNC, AND, functions[r]);
		start++;
		setup_argv(&stacks->func->root->func, argv, &start, functions);
            }
        }
        else
        {
            if ((r = is_operator(argv[start])) != -1)
            {
                enum operator op = r;
                stacks->func = push(stacks->op, OPERATOR, op, functions[0]);
		start++;
            }
        }
    }
}

static struct tree *fill_tree(struct stacks *stacks)
{
    struct tree *root = pop(stacks->func);
    struct tree *root_save = root;
    if (stacks->op)
    {
        struct tree *new_op = pop(stacks->op);
        new_op->rson = root;
        root = new_op;
	root_save = root;
        while (stacks->op)
        {
            root->lson = pop(stacks->op);
	    root = root->lson;
            if (stacks->func)
            {
                struct tree *new_func = pop(stacks->func);
                root->rson = new_func;
            }
        }
	if (stacks->func)
	{
	    root->lson = pop(stacks->func);
	}
    }
    return root_save;
}

struct tree *setup_tree(struct function *functions, char *argv[], int start)
{
    if (!argv[start])
    {
	return NULL;
    }
    struct stacks stacks =
        {
            NULL, NULL
        };
    fill_stacks(&stacks, argv, start, functions);
    struct tree *root = fill_tree(&stacks);
    return root;
}

void destroy_tree(struct tree *root)
{
    if (!root)
    {
        return;
    }
    destroy_tree(root->lson);
    destroy_tree(root->rson);
    if (root->func.argv)
    {
	free(root->func.argv);
    }
    free(root);
}
