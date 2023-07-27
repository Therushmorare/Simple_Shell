#include "shell.h"

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
	int argc = 0, i = 0, is_on = 1, exec, status, exit_status, last_exit = 0;
	const char *delim = " \n", *path = getenv("PATH");
	pid_t pid;
	char full_path[1024], *path_copy, **argv = NULL, *token1, *key, *value;
	struct stat st;

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
	       	i =0;
		free(argv);
		argv = NULL;
		
		
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
		
              	path_copy = strdup(path);
               	token = strtok(path_copy, ":");
               	while (token)
           	{
             		snprintf(full_path, sizeof(full_path), "%s/%s", token, argv[0]);
			if (stat(full_path, &st) == 0 || stat(argv[0], &st) == 0)
			{
				
				/*printf("innn argv[0]-> %s\n", argv[0]);*/	
				pid = fork();
				if (pid == 0)
				{
					exec = execve(full_path, argv, environ);
					if (exec == -1)
					{
						if (execve(argv[0], argv, environ) == -1)
						{
							fprintf(stderr, "./shell: No such file or directory\n");
							is_on = 0;
						}
					}
				}
				else
				{
					wait(&status);
					last_exit = WEXITSTATUS(status);
				}
				break;

			}
			if (stat(full_path, &st) != 0 || stat(argv[0], &st) != 0)
			{
				fprintf(stderr, "./shell: No such file or directory\n");
			}
			token = strtok(NULL, ":");

		}
		


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
		
		free(command_copy), free(path_copy);	
	}

		free(command), free(command_copy), free(path_copy), free(argv);

		return (0);
}
