iinclude <stdio.h>

#include <stdlib.h>

#include <string.h>

#include <unistd.h>

#include <sys/wait.h>



int main(void)

{

        char *cmp = NULL, *cmp_cpy = NULL, *token = NULL;

        char *delim = " \n";

        size_t n = 0;

        int argc = 0, i = 0, exec;

        char **argv = NULL;

        int is_on = 1, integer;

        pid_t pid, waiter;



        while (is_on)

        {



        printf(":) ");

        pid = fork();

        //var = getline(...);

        if (getline(&cmp, &n, stdin) == -1)

                return (-1);



        cmp_cpy = strdup(cmp);



        token = strtok(cmp, delim); //cmp = "The river is flowing"



        while(token != NULL)

        {

	token = strtok(NULL, delim);

                argc++;

        }



        argv = malloc(sizeof(char *) * argc);



        token = strtok(cmp_cpy, delim);

        while(token)

        {

                argv[i] = token;

                token = strtok(NULL, delim);

                i++;

        }

        argv[i] = NULL;



        if (pid == 0)

        {

                printf("in child\n");

                exec = execve(argv[0], argv, NULL);

                if (exec == -1)

                        is_on = 0;

                        //return -1;

        }

        else

        {

                printf("in parent\n");

                //is_on = 0;

                //      waiter = wait(&integer);

        //      free(cmp), free(argv);
	}
	}
}
