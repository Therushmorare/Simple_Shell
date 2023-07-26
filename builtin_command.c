#include <stdio.h>
#include <string.h>

char **s = environ;

int builtin_command(const char* inpCommand)
{
	int i;
	const char* built_ins_arr[] = {
		"exit", "env", "setenv", "unsetenv", "echo"
	};

	for (i = 0; i < sizeof(built_ins_arr) / sizeof(built_ins_arr[0]); ++i) 
	{
		if (strcmp(inpCommand, built_ins_arr[i]) == 0)
		{
			exit(127);
		}
	}

	return 0;
}

//application of function
if (strncmp(command, "exit") == 0)
{
	if (builtin_command(command))
	{
		exit(0);
	}
}
else if (strncmp(command, "exit", 4))
{
	token = strtok(command, delim);
	if (builtin_command(token))
	{
		token = strtok(NULL, delim);
		exit_status = atoi(token);
		exit(exit_status);
	}
}


if (strncmp(command, "env") == 0)
{
	if (builtin_command(command))
	{

		for (; *s; s++)
		{
			//printf("%s\n", *s);
			fputs(*s, stdout);
		}

	}

}

if (strncmp(command, "setenv", 6) == 0)
{
	token1 = strtok(command, delim);
	if (builtin_command(token1))
	{
		token1 = strtok(NULL, delim);

		token = strtok(token1, "=");
		key = token;
		token = strtok(NULL, "=");
		value = token;

		setenv(key, value, 1);
	}
}

if (strncmp(command, "unsetenv", 8) == 0)
{
	token = strtok(command, delim);
	if (builtin_command(token))
	{
		token = strtok(NULL, delim);
		unsetenv(token);
	}
}
