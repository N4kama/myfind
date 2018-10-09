#include "find.h"

struct tree *create_tree(char *s)
{
    struct tree *new = malloc(sizeof(struct tree));
    if (!new)
    {
	return NULL;
    }
    new->path = s;
    new->sibling = NULL;
    new->children = NULL;
    return new;
}

void add_child(struct tree *root, struct tree *child)
{
    if (!root->children)
    {
	root->children = child;
	return;
    }
    root = root->children;
    if (!root->sibling)
    {
	root->sibling = child;
	return;
    }
    for (; root->sibling; root = root->sibling)
    {
	continue;
    }
    root->sibling = child;
}

void clear_tree_rec(struct tree *root)
{
    if (!root)
    {
	return;
    }
    for (struct tree *child = root->children; child; child = child->children)
    {
	clear_tree(child);
    }
    struct tree *tmp = NULL;
    for (struct tree *brother = root; brother; brother = tmp)
    {
	tmp = brother->sibling;
	free(brother->path);
	free(brother);
    }
}

void clear_tree(struct tree *root)
{
    //Do not need to free the root path string.
    clear_tree_rec(root->children);
    free(root);
}