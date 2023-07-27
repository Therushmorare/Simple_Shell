#include <shell.h>

/**
 * exit_func - function to be used to exit shell
 * @chars_input: shell command
 * Return: 0
 */

void exit_func(char **chars_input)
{
	if (strncmp(chars_input, "exit") == 0)
	{
		if (builtin_checker(chars_input))
			exit(0);
	}
	else if (strncmp(chars_input, "exit", 4))
	{
		token = strtok(chars_input, delim);
		if (builtin_checker(token))
		{
			token = strtok(NULL, delim);
			exit_status = atoi(token);
			exit(exit_status);
		}
	}
	else
	{
		exit(127);
	}

	return (0);
}
