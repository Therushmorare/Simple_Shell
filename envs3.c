#include <shell.h>

/**
 * unsetenv_func -  function that unsets the env
 * @chars_input: shell command
 * Return: 0
 */

void unsetenv_func(char *chars_input)
{
	if (strncmp(chars_input, "unsetenv", 8) == 0)
	{
		token = strtok(command, delim);
		if (builtin_checker(token))
		{
			token = strtok(NULL, delim);
			unsetenv(token);
		}
	}

	return (0);
}
