#ifndef FIND_H
# define FIND_H

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <err.h>

#include "string.h"

struct options
{
    int return_value;
};

struct tree
{
    char *path;
    struct tree *sibling;
    struct tree *children;
};

int is_dir(char *path, struct options *opt);
void fill_tree(struct tree *root, struct options *opt);
void find(char *path, struct options *opt);

struct tree *create_tree(char *s);
void add_child(struct tree *root, struct tree *child);
void print_tree(struct tree *root, struct options *opt);
void clear_tree(struct tree *root);

#endif /* !FIND_H */