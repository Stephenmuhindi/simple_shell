/**
 * print_env - a function that prints the enviroment
 */
#include <unistd.h>
#include "shell.h"

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
}
