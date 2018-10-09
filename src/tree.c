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

void print_tree(struct tree *root, struct options *opt)
{
    if (!root)
    {
        return;
    }
    printf("%s\n", root->path);
    if (!is_dir(root->path, opt))
    {
	return;
    }
    root = root->children;
    for (; root; root = root->sibling)
    {
        print_tree(root, opt);
    }
}

void clear_tree_rec(struct tree *root)
{
    struct tree *tmp = NULL;
    for (; root; root = tmp)
    {
	clear_tree_rec(root->children);
        tmp = root->sibling;
        free(root->path);
        free(root);
    }
}

void clear_tree(struct tree *root)
{
    //Do not need to free the root path string.
    clear_tree_rec(root->children);
    free(root);
}