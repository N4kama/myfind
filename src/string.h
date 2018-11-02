#ifndef STRING_H
#define STRING_H

#include <stdio.h>

size_t my_strlen(char *s);
void my_path_concat(char *dst, char *path, char *new);
unsigned int my_strcmp(char *a, char *b);
void my_strcpy(char *dst, char *src);
void fill_str_cmd(char *argv[], unsigned int *start, char ***new);
int *replace_with_path(char *path, char *argv[]);
void replace_path(char *s[], int *arr);

#endif /* !STRING_H */