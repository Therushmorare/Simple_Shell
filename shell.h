#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>

extern char **environ;
int builtin_checker(const char *user_command);
void exit_func(char *chars_input);
void setenv_func(char **chars_input);
void unsetenv_func(char **chars_input);
#endif
