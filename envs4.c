#include "shell.h"

/**
 * env_func - function that prints environment variables
 * @chars_input: shell command
 *
 * Return: 0;
 */

void env_func(char *chars_input)
{
	char **env_string = environ;

	if (builtin_checker(chars_input))
	{
		if (strcmp(chars_input, "env") == 0)
		{
			for (; *env_string; env_string++)
			{
				printf("%s\n", *env_string);
			}
		}
	}

}
