#ifndef _SHELL_H
#define _SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>

extern char **environ;
char *fullpath(char **argv, char *path);
int childprocess(char **argv, char *command, char *fullpath);
char *get_command(void);
int countPATH(char *path);
void exit_func(char *chars_input);
void setenv_func(char *chars_input);
void unsetenv_func(char *chars_input);
int builtin_checker(const char *user_command);

#endif
