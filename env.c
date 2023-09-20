#include <unistd.h>
#include "shell.h"
/**
 * print_env - a function that prints the enviroment
 */

extern char **environ;

void print_env(void)
{
    char **env = environ;

    while (*env)
    {
        write(STDOUT_FILENO, *env, strlen(*env));
        write(STDOUT_FILENO, "\n", 1);
        env++;
    }
	char **env = environ;

	while (*env)
	{
		write(STDOUT_FILENO, *env, strlen(*env));
		write(STDOUT_FILENO, "\n", 1);
		env++;
	}
}
