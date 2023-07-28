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
	int argc = 0, i = 0, is_on = 1, exit_status, last_exit = 0;
	char *delim = " \n", *path = getenv("PATH"), *buffer = NULL;
	char full_path[1024], **argv, *token1, *key, *value;

	while (is_on)
	{
		printf("%s", shell_prompt_symb);
		argv = NULL;
		argc = 0;
		buffer = get_command();
		if (*buffer != '\0')
		{
                
		
		
		command_copy = strdup(buffer);

               	token = strtok(buffer, delim);
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
		 
		

		/*
		if (strcmp(buffer, "exit") == 0)
		{
			exit(0);
		}
		else if (strncmp(buffer, "exit",  4) == 0)
		{
			token = strtok(buffer, delim);
			token = strtok(NULL, delim);
			exit_status = atoi(token);

			exit(exit_status);
		}

		if (strncmp(buffer, "setenv", 6) == 0)
		{
			token1 = strtok(buffer, delim);
			token1 = strtok(NULL, delim);

			token = strtok(token1, "=");
			key = token;
			token = strtok(NULL, "=");
			value = token;

			setenv(key, value, 1);
		}
		if (strncmp(buffer, "unsetenv", 8) == 0)
		{
			token = strtok(buffer, delim);
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
		}*/
		

		
		strcpy(full_path, fullpath(argv, path));
		printf("in new_test.c - argv[0] = %s\n", argv[0]);
		printf("full path = %s\n", full_path);
		exit_status = childprocess(argv, command, full_path);
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
