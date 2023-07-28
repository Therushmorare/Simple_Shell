#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/**
 *builtin_checker - checks if command is a builtin
 *@user_command: the command to be checked
 *Return: zero
 */

int builtin_checker(const char *user_command)
{
	long unsigned int i;
	const char *builtins[] = {
	"env", "setenv", "exit", "unsetenv", "cd"
	};
	i = 0;
	for (i = 0; i < sizeof(builtins) / sizeof(builtins[0]); ++i)
	{
		if (strcmp(user_command, builtins[i]) == 0)
		{
			return (1);
			exit(127);
		}
	}

	return (0);
}
