#include "shell.h"
int childprocess(char **argv, char *command, char *fullpath);
char *fullpath(char **argv, char *path);
/**
 * main - function that creates a shell
 *
 * Return: always 0
 */

int main(void)
{
	char *shell_prompt_symb = "($) ", *command = NULL, *command_copy = NULL, *token;
	ssize_t chars_input;
	size_t n = 0;
	int argc = 0, i = 0, is_on = 1, exit_status, last_exit = 0;
	char *delim = " \n", *path = getenv("PATH");
	char full_path[1024], **argv = NULL, *token1, *key, *value;

	while (is_on)
	{
		printf("%s", shell_prompt_symb);
		chars_input = getline(&command, &n, stdin);

		if (chars_input == -1)
		{
			printf("\n");
			return (-1);
		}
		if (command[chars_input - 1] == '\n')
		{
			command[chars_input - 1] = '\0';
		}
                argc = 0;
		
		
		command_copy = strdup(command);

               	token = strtok(command, delim);
               	while (token)
              	{
               		token = strtok(NULL, delim);
               		argc++;
             	}

          	argv = malloc(sizeof(char *) * argc);

             	token = strtok(command_copy, delim);
              	while (token)
             	{
               		argv[i] = token;
                	token = strtok(NULL, delim);
               		i++;
    		}
        	argv[i] = NULL;
		 
		


		if (strcmp(command, "exit") == 0)
		{
			exit(0);
		}
		else if (strncmp(command, "exit",  4) == 0)
		{
			token = strtok(command, delim);
			token = strtok(NULL, delim);
			exit_status = atoi(token);

			exit(exit_status);
		}

		if (strncmp(command, "setenv", 6) == 0)
		{
			token1 = strtok(command, delim);
			token1 = strtok(NULL, delim);

			token = strtok(token1, "=");
			key = token;
			token = strtok(NULL, "=");
			value = token;

			setenv(key, value, 1);
		}
		if (strncmp(command, "unsetenv", 8) == 0)
		{
			token = strtok(command, delim);
			token = strtok(NULL, delim);

			unsetenv(token);
		}

		if (strcmp(command, "echo $$") == 0)
		{
			fprintf(stdout, "%u\n", getppid());
		}
	
		if (strcmp(command, "echo $PATH") == 0)
		{
			fprintf(stdout, "%s\n", path);
		}
		if (strcmp(command, "echo $?") == 0)
		{
			fprintf(stdout, "%d\n", last_exit);
		}
		

		
		full_path = fullpath(argv, path);
		exit_status = childprocess(argv, command, full_path);

	}

		/*free(command), free(command_copy), free(path_copy), free(argv);*/

		return (0);
}
