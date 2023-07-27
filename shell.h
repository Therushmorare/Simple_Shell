#ifndef _SHELL_H
#define _SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

char *fullpath(char **argv, char *path);
int childprocess(char **argv, char *command, char *fullpath);

#endif
