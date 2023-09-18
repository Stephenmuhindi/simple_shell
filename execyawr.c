#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include "main.h"

int executeCommand(char *tokens[]);

int executeCommand(char *tokens[])
{
	struct stat command_stat;

	if (stat(tokens[0], &command_stat) == 0)
	{
		pid_t pid = fork();

		if (pid < 0)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		else if (pid == 0)
		{
			if (execvp(tokens[0], tokens) == -1)
			{
				perror("execvp");
				exit(EXIT_FAILURE);
			}
		}
		else
		{
			int status;

			if (wait(&status) == -1)
			{
				perror("wait");
				exit(EXIT_FAILURE);
			}
		}
	}
	else
	{
		char error_message[100];
		snprintf(error_message, sizeof(error_message), "Command not found: %s\n", tokens[0]);
		write(STDOUT_FILENO, error_message, strlen(error_message));
	}
	return (0);
}
