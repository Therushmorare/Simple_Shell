#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>

extern char **environ;

int main(void)
{
	char *shell_prompt_symb = "$ ";
	char *command = NULL;
	char *command_copy = NULL;
	ssize_t chars_input;
	size_t n = 0;
	int argc = 0, i = 0, is_on = 1, exec, status;
	const char *delim = " \n";
	char *token;
	char **argv = NULL;
	pid_t pid;
	char *path_copy;
	char full_path[1024];

	while(is_on)
	{
		printf("%s", shell_prompt_symb);

		chars_input = getline(&command, &n, stdin);
		
		if(chars_input == -1)
                {
			printf("No input provided\n");
			return (-1);
                }
                if (command[chars_input - 1] == '\n')
                {
			command[chars_input - 1] = '\0';
                }

                if (strcmp(command, "exit") == 0) {
			exit(0);
                }

		pid = fork();

		if (pid == 0)
		{

			command_copy = strdup(command);

			token = strtok(command, delim);
			while (token)
			{
				token = strtok(NULL, delim);
				argc++;
			}

			argv = malloc(sizeof(char *) * argc);

			token = strtok(command_copy, delim);
			while(token)
			{
				argv[i] = token;
				token = strtok(NULL, delim);
				i++;
			}
			argv[i] = NULL;

			
			const char *path = getenv("PATH");	
			path_copy = strdup(path);
			token = strtok(path_copy, ":");
			while (token)
			{
				snprintf(full_path, sizeof(full_path), "%s/%s", token, argv[0]);
	
				struct stat st;
				
				if (stat(full_path, &st) == 0)
				{
					argv[0] = full_path;
					exec = execve(argv[0], argv, environ);
					if (exec == -1)
					{
						printf(":-(\n");
						is_on = 0;
					}
				}
				token = strtok(NULL, ":");
			}
			
			exec = execve(argv[0], argv, environ);
			if (exec == -1)
			{
				printf(":( command not found\n");
				is_on = 0;
			}
		}
		else
		{
			wait(&status);
		}
	
	}
			
			free(command), free(command_copy), free(argv);

			return (0);
		}
