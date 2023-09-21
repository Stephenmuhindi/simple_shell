#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

extern char **environ;

#define MAX_INPUT_LENGTH 1024
#define MAX_TOKENS 10

/**
 * parse_command -  Function to parse the command line into tokens.
 * @input: input command line.
 * @tokens: array to store the parsed tokens.
 * Return: number of tokens found.
 */
int parse_command(char *input, char *tokens[])
{
	int token_count = 0;
	char *token = strtok(input, " \t\n");
	int length = strlen(tokens[token_count - 1]);

	while (token != NULL && token_count < MAX_TOKENS)
	{
		tokens[token_count] = token;
		token_count++;
		token = strtok(NULL, " \t\n");
	}
	if (length > 0 && tokens[token_count - 1][length - 1] == '\n')
	{
		tokens[token_count - 1][length - 1] = '\0';
	}

	tokens[token_count] = NULL;
	return (token_count);
}

/**
 * execute_command - Function to execute
 * @tokens: An array of strings containing the command and its arguments.
 * Return: 0 if executed
 */
int execute_command(char *tokens[])
{
	int status;
	pid_t pid;

	if (access(tokens[0], X_OK) == -1)
	{
		perror("Command not found");
		return (1);
	}

	pid = fork();

	if (pid < 0)
	{
		perror("Fork failed");
		return (1);
	}

	if (pid == 0)
	{
		if (strcmp(tokens[0], "exit") == 0)
		{
			exit(0);
		} else if (strcmp(tokens[0], "cd") == 0)
		{
			if (tokens[1] != NULL)
			{
				if (chdir(tokens[1]) != 0)
				{
					perror("cd");
					exit(1);
				}
			}
			exit(0);
		} else if (strcmp(tokens[0], "env") == 0)
		{
			char **env = environ;

			while (*env != NULL)
			{
				printf("%s\n", *env);
				env++;
			}
			exit(0);
		}
		if (execvp(tokens[0], tokens) == -1)
		{
			perror("Command not found");
			exit(1);
		}
	} else
	{
		waitpid(pid, &status, 0);
		return (WEXITSTATUS(status));
	}
	return (0);
}

/**
 * main - entry point for the shell
 * @tokens: An array of command tokens
 *
 * Return: 0 on successful execution of the shell.
 */
int main(void)
{
	char input[MAX_INPUT_LENGTH];
	char *tokens[MAX_TOKENS];
	int token_count;

	while (1)
	{
		if (write(STDOUT_FILENO, "$ ", 20) == -1)
		{
			perror("Write failed");
			return (1);
		}
		if (fgets(input, sizeof(input), stdin) == NULL)
		{
			if (write(STDOUT_FILENO, "\n", 1) == -1)
			{
				perror("Write failed");
				return (1);
			}
			break;
		}
		token_count = parse_command(input, tokens);
		if (token_count > 0)
		{
			int result = execute_command(tokens);

			if (result != 0)
			{
				char error_msg[64];

				snprintf(error_msg, sizeof(error_msg), "Command failed %d\n", result);
				if (write(STDERR_FILENO, error_msg, strlen(error_msg)) == -1)
				{
					perror("Write failed");
					return (1);
				}
			}
		}
	}

	return (0);
}
