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
	//char *ext_command = NULL;
	ssize_t chars_input;
	size_t n = 0;
	int argc = 0, i = 0, is_on = 1, exec, status;
	int j;
	const char *delim = " \n";
	char *token;
	char **argv = NULL;
	pid_t pid;  //waiter;
	//const char *path = getenv("PATH");
	char *path_copy;
	//char full_path[1024];

	//run the shell in an infinite loop only to be exited by the exit() sys call
	while(is_on)
	{
		//shell prompt symb
		printf("%s", shell_prompt_symb);

		//get user input and print it
		chars_input = getline(&command, &n, stdin);
		
		//validate getline, use -1 as condition check since it returns -1 on success
		if(chars_input == -1)//remeber this is what we spoke about during our meeting
                {
			printf("No input provided\n");
			return (-1);
                }
                if (command[chars_input - 1] == '\n')
                {
			command[chars_input - 1] = '\0';
                }

                // Compare the string with exit
                if (strcmp(command, "exit") == 0) {
			exit(0);
                }
		printf("before env\n");
		if (strcmp(command, "env") == 0)
		{
			for(j = 0; environ[j] != NULL;  j++)
			{
				printf("%s\n", environ[j]);
			}
		}

		pid = fork();

		if (pid == 0)
		{
			printf("in child\n");
			/*//shell prompt symb
			printf("%s", shell_prompt_symb);

			//get user input and print it
			chars_input = getline(&command, &n, stdin);
			

			//validate getline, use -1 as condition check since it returns -1 on success
			if(chars_input == -1)//remeber this is what we spoke about during our meeting
			{
				printf("No input provided\n");
				return (-1);
			}
			if (command[chars_input - 1] == '\n')
			{
				command[chars_input - 1] = '\0';
			}

			// Compare the string with exit
			if (strcmp(command, "jelly") == 0) {
				exit(0);
			}
			else 
			{
        			printf("You did not enter 'jelly'.\n");
			}*/

			//print user command back
			//printf("%s\n", user_input);//and i told you about printing the getline values

		/**
		 * before using execution commands and system calls
		 * all i need is to tokenize user_input by saving it to user_input_cpy
		 * save the user_input_cpy in tokens
		 * use tokens to validate user input 
		 */


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
				char full_path[1024];
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
			//waiter = wait(&status);
			printf("in parent\n");
			wait(&status);
			printf("in parent 2.0\n");
			//free(command), free(command_copy), free(argv);
		}
	
	}
			
			free(command), free(command_copy), free(argv);

			return (0);
		}
	
