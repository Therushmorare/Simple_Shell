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
	pid_t pid, waiter;
	//const char *path = getenv("PATH");
	char *path_copy;
	char full_path[1024];

	//run the shell in an infinite loop only to be exited by the exit() sys call
	while(is_on)
	{
		/*
		//pid = fork();
		printf("Iteration\n");
		printf("%s", shell_prompt_symb);

                        //get user input and print it
                chars_input = getline(&command, &n, stdin);

                        //validate getline, use -1 as condition check since it returns -1 on success
                 if(chars_input == -1)//remeber this is what we spoke about during our meeting
                        {
                                printf("No input provided\n");
                                return (-1);
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
                        while(token)
                        {
                                argv[i] = token;
                                token = strtok(NULL, delim);
                                i++;
                        }
                        argv[i] = NULL;


                        //printf("argv[0]: %s\n", argv[0]);
                        if (strcmp(argv[0], "exit") == 0)
                        {
                                //printf("exit here\n");
                                is_on = 0;
                                exit(0);
                               // break;

                                //system("exit");
			}*/
		pid = fork();
		if (pid == 0)
		{
			//printf("argv[0] in child: %s\n", argv[0]);
			
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
			
			
			printf("argv[0]: %s\n", argv[0]);
			if (strcmp(argv[0], "exit") == 0)
			{
				printf("exit here\n");
				is_on = 0;
				//exit(0);
				break;
				
				system("exit");
			}
			printf("after exit\n");	
			
			printf("in child process\n");
			printf("argv[0] in child: %s\n", argv[0]);
			const char *path = getenv("PATH");	
			path_copy = strdup(path);
			token = strtok(path_copy, ":");
			while (token)
			{
				//char full_path[1024];
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
			printf("in parent process\n");
			//printf("argv[0]: %s\n", argv[0]);
                        /*if (strcmp(argv[0], "exit") == 0)
                        {
                                printf("exit here\n");
                                is_on = 0;
                                //exit(0);
                        //      break;

                                system("exit");
                        }
                        printf("after exit\n");*/
	//		printf("argv[0] in child: %s\n", argv[0]);
			waiter = wait(&status);
			printf("in parent process again\n");
			free(command), free(command_copy), free(argv);
		}
		//free(command), free(command_copy), free(argv), free(path_copy);
	}
	return (0);
}
