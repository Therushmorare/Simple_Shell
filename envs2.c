#include "shell.h"

/**
 * setenv_func - this function sets the env
 * @chars_input: shell command
 * Return: 0
 */

void setenv_func(char *chars_input)
{
	char *token, *token1, *key, *value;
	char *delim = " \n";
	
	
	if (strncmp(chars_input, "setenv", 6) == 0)
	{
		token1 = strtok(chars_input, delim);
		if (builtin_checker(token1))
		{
			token1 = strtok(NULL, delim);
			token = strtok(token1, "=");
			key = token;
			token = strtok(NULL, "=");
			value = token;
			setenv(key, value, 1);
		}
	}
	return;
}
