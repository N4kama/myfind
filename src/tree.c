#include "find.h"

struct tree *create_tree(enum mode mode, enum operator op, struct function func)
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

struct tree *setup_tree(struct function *functions, char *argv[], int start)
{
    //BULLSHIT
    //BULLSHIT
//Handle parenthesis first, then operator, funcs
    if (functions)
    {
	//BULLSHIT
/*
        struct tree *root = create_tree(OPERATOR, AND, functions[0]);
	root->lson = create_tree(FUNC, AND, functions[0]);
	root->rson = create_tree(FUNC, AND, functions[1]);
	return root;*/
	return NULL;
    }
    if (argv && start)
    {
	return NULL;
    }
    return NULL;
}

void destroy_tree(struct tree *root)
{
    if (!root)
    {
	return;
    }
    destroy_tree(root->lson);
    destroy_tree(root->rson);
    free(root);
}
