#include "shell.h"

/**
 * fullpath - string to call execve on
 * @argv: argv
 * @path: PATH
 *
 * Return: fullpath
 */

char *fullpath(char **argv, char *path)
{
	char *token, *fullpath = NULL, *path_copy = NULL;
	int pathflag = 0;
       	struct stat st;

	path_copy = strdup(path);
	token = strtok(path_copy, "=");
	while (token)
	{
		snprintf(full_path, sizeof(full_path), "%s/%s", token, argv[0]);

		if (stat(fullpath, &st) == 0)
		{
			pathflag = 1;
			break;
		}
		else if (stat(argv[0], &st) == 0)
		{
			fullpath = argv[0];
			pathflag = 1;
			break;
		}
		token = strtok(NULL, ":");
	}
	if (pathflag == 0)
	{
		fullpath = argv[0];
	}
	free(path_copy);
	return (fullpath);


}


/**
 * childprocess - function responsible for execution
 * @argv: argv
 * @command: command from getline
 * @fullpath: command from fullpath
 *
 * Return: 0
 */

int childprocess(char **argv, char *command, char *fullpath)
{
	int i, exec, status, exit_status = 0;
	pid_t pid;

	pid = fork();
	if (pid == -1)
	{
		fprintf(stderr, "fork failed\n");
		exit(1);
	}
	else if (pid == 0)
	{
		exec = execve(fullpath, argv, environ);
		if (exec == -1)
		{
			fprintf(stderr, "./shell: No such file or directory\n");
			i = 0;
			for (i = 0; argv[i] != NULL; i++)
			{
				free(argv[i]);
				argv[i] = NULL;
			}
			free(argv);
			free(command);
			exit(127);
		}
		else
		{
			wait(&status);
			exit_status = WEXITSTATUS(status);
		}
		i = 0;
		for (i = 0; argv[i] != NULL; i++)
		{
			free(argv[i]);
			argv[i] = NULL;
		}
		free(argv);
		free(command);
	}
	return (exit_status);
}
