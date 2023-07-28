#include "shell.h"

/**
 * main - function that creates a shell
 *
 * Return: always 0
 */

int main(void)
{
	char *command = NULL;
	int is_on = 1;
	char *path = getenv("PATH");
	char full_path[1024], **argv;

	while (is_on)
	{
		argv = NULL;
		printf("#cisfun$ ");
		command = get_command();
		if (*command != '\0')
		{
			argv = argv_tokenize(command);
			if (argv == NULL)
			{
				free(command);
				continue;
			}
			/*env_func(command);*/
			setenv_func(command);
			unsetenv_func(command);
			exit_func(command);
			strcpy(full_path, fullpath(argv, path));
			childprocess(argv, command, full_path);

		}
		else
		{
			free(command);
			exit(127);
		}
	}
		return (0);
}
