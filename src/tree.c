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

void fill_tree()
{
    //Fill the tree (read the cmd, func and priorities)
}

struct tree *setup_tree(struct function *functions, char *argv[], int start)
{
    //FIXME
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
