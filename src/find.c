#include "find.h"

void fill_tree(struct tree *root)
{
    DIR *dir = opendir(root->path);
    if (!dir)
    {
	fprintf(stderr, "find: ‘%s’: No such file or directory\n", root->path);
    }
    else
    {
	struct dirent *cur = readdir(dir);
	readdir(dir);
	for (cur = readdir(dir); cur; cur = readdir(dir))
	{
	    size_t new_len = my_strlen(root->path) + my_strlen(cur->d_name);
	    char *new_path = malloc(new_len * sizeof(char));
	    my_path_concat(new_path, root->path, cur->d_name, new_len);
	    struct tree *new = create_tree(new_path);
	    add_child(root, new);
	}
	for (struct tree *child = root->children; child; child = child->sibling)
	{
	    fill_tree(child);
	}
    }
    closedir(dir);
}

void find(char *path)
{
    struct tree *root = create_tree(path);
    fill_tree(root);
    print_tree(root);
    clear_tree(root);
}