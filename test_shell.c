#include "shell.h"

/**
 * main - function that creates a shell
 *
 * Return: always 0
 */

int main(void)
{
        char *shell_prompt_symb = "($) ", *command = NULL;
        ssize_t chars_input;
        size_t n = 0;
        int  is_on = 1;
        //const char *delim = " \n", *path = getenv("PATH");
        //pid_t pid;
        //char full_path[3000], *path_copy, **argv = NULL, *token1, *key, *value;
        //struct stat st;

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

		/* code to be tested*/
		if (strcmp(command, "env") == 0)
		{
			env_func(command);
		}
		else if (strcmp(command, "setenv") == 0)
		{
			setenv_func(command);
		}
		else if (strcmp(command, "unsetenv") == 0)
		{
			unsetenv_func(command);
		}
		else
		{
			exit_func(command);
		}
		//env_func(command);
		//setenv_func(command);
		//unsetenv_func(command);
		//exit_func(command);
		
	}
}
