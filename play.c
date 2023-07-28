#include "shell.h"

/**
 * main - function that creates a shell
 *
 * Return: always 0
 */

int main(void)
{
	char *buffer = NULL, *command_copy = NULL, *token;
	int argc = 0, i = 0, is_on = 1, exit_status, last_exit = 0;
	char *delim = " \n", *path = getenv("PATH");
	char full_path[1024], **argv, *token1, *key, *value;

	
	while (is_on)
	{
		
		argv = NULL;
		/*display_prompt();*/
		printf("($) ");
		buffer = get_command();
		if (*buffer != '\0')
		{
			argv = argv_tokenize(buffer);
			if (argv == NULL)
			{
				free(buffer);
				continue;
			}

		
			strcpy(full_path, fullpath(argv, path));
			printf("in new_test.c - argv[0] = %s\n", argv[0]);
			printf("full path = %s\n", full_path);
			exit_status = childprocess(argv, buffer, full_path);
		/*free(command_copy);*/
	
		}
		else
		{
			free(buffer);
		}
	}
		

		
		/*free(command);*/
		return (0);
}
