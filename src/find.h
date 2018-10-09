#ifndef FIND_H
# define FIND_H

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>

struct options
{
    int this_is_test;
};

struct tree
{
    char *path;
    struct tree *sibling;
    struct tree *children;
};

struct tree *create_tree(char *s);
void add_child(struct tree *root, struct tree *child);
void print_tree(struct tree *root);
void clear_tree(struct tree *root);

size_t my_strlen(char *s);
void my_path_concat(char *dst, char *path, char *new, size_t len);

void fill_tree(struct tree *root);
void find(char *path);

#endif /* !FIND_H */