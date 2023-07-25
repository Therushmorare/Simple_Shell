#include "shell.h"

int call_env(const char *name, const char *value, int overwrite);

/**
 * main - function that creates a shell
 *
 * Return: always 0
 */

int main(void)
{
	char *shell_prompt_symb = "$ ", *command = NULL, *command_copy = NULL, *token;
	ssize_t chars_input;
	size_t n = 0;
	int argc = 0, i = 0, is_on = 1, exec, status, exit_status, set_status;
	const char *delim = " \n", *path = getenv("PATH");
	pid_t pid;
	char full_path[1024], *path_copy, **argv = NULL, *token1, *key, *value;

	while (is_on)
	{
		printf("%s", shell_prompt_symb);
		chars_input = getline(&command, &n, stdin);

		if (chars_input == -1)
		{
			printf("No input provided\n");
			return (-1);
		}
		if (command[chars_input - 1] == '\n')
		{
			command[chars_input - 1] = '\0';
		}

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

		/*
	 if (strcmp(command, "setenv") == 0) {
         if (argc != 3) {
         fprintf(stderr, "setenv: Incorrect number of arguments\n");
         return 1;
        }
else{
        //assume we tokenized the string
        call_env(token1, token2, token3);
	*/
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
		
		pid = fork();
		if (pid == 0)
		{
		/*
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
		*/

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

		free(command), free(command_copy), free(argv), free(path_copy);

		return (0);
}


/**
 * call_env - sets an environment variable
 * @name: variable
 * @value: value
 * @overwrite: int to determine whether to overwrite a value or not
 *
 * Return: on success 0, otherwise -1
 */

int call_env(const char *name, const char *value, int overwrite)
{
	setenv(name, value, overwrite);
}
