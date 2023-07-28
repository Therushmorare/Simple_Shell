#include "shell.h"

/**
 * unsetenv_func -  function that unsets the env
 * @chars_input: shell command
 * Return: 0
 */

void unsetenv_func(char *chars_input)
{
	char *token;
	char *delim = " \n";

	if (strncmp(chars_input, "unsetenv", 8) == 0)
	{
		token = strtok(chars_input, delim);
		if (builtin_checker(token))
		{
			token = strtok(NULL, delim);
			unsetenv(token);
		}
	}
}
