#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main(int ac, char **argv)
{
	char *shell_prompt_symb = "$";
	char *user_input=NULL;
	char *user_input_cpy=NULL;
	ssize_t chars_input;
	size_t itr = 0;
	int i = 0;
	const char *delim = "\n";
	char *str_tokens;
	char **argv;
	int tokens_len = 0;

	//run the shell in an infinite loop only to be exited by the exit() sys call
	while(1)
	{
		//shell prompt symb
		printf("%s", shell_prompt_symb);

		//get user input and print it
		chars_input = getline(&user_input, &itr, stdin);

		//validate getline, use -1 as condition check since it returns -1 on success
		if(chars_input == -1)//remeber this is what we spoke about during our meeting
		{
			printf("No input provided\n");
			return (-1);
		}

		//print user command back
		printf("%s\n", user_input);//and i told you about printing the getline values

		/**
		 * before using execution commands and system calls
		 * all i need is to tokenize user_input by saving it to user_input_cpy
		 * save the user_input_cpy in tokens
		 * use tokens to validate user input 
		 */


		free(user_input);
	}

	return (0);
}
