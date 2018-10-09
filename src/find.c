#include "find.h"

int is_dir(char *path, struct options *opt)
{
    struct stat st;
    if (stat(path, &st))
    {
	warnx("cannot do stat: Error while with stats of file : %s", path);
	opt->return_value = 1;
    }
    if (S_ISDIR(st.st_mode))
    {
	return 1;
    }
    return 0;
}

void fill_tree(struct tree *root, struct options *opt)
{
    DIR *dir = opendir(root->path);
    if (!dir)
    {
	warnx("cannot do opendir: ‘%s’ --> No such file or directory",
	      root->path);
	opt->return_value = 1;
    }
    else
    {
	struct dirent *cur = readdir(dir);
	readdir(dir);
	for (cur = readdir(dir); cur; cur = readdir(dir))
	{
	    size_t new_len = my_strlen(root->path) + my_strlen(cur->d_name) + 2;
	    char *new_path = malloc(new_len * sizeof(char));
	    my_path_concat(new_path, root->path, cur->d_name);
	    struct tree *new = create_tree(new_path);
	    add_child(root, new);
	}
	for (struct tree *child = root->children; child; child = child->sibling)
	{
	    if (is_dir(child->path, opt))
	    {
		fill_tree(child, opt);
	    }
	}
    }
    closedir(dir);
}

void find(char *path, struct options *opt)
{
    struct tree *root = create_tree(path);
    fill_tree(root, opt);
    print_tree(root, opt);
    clear_tree(root);
}