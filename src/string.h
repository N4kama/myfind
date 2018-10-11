#ifndef STRING_H
# define STRING_H

#include <stdio.h>

size_t my_strlen(char *s);
void my_path_concat(char *dst, char *path, char *new);
unsigned int my_strcmp(char *a, char *b);

#endif /* !STRING_H */