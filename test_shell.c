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
		exit_func(command);
	}
}
