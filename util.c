#include "shell.h"

void tokenize_input(char *input, char *tokens[], int *token_count)
{
	char *token;
	*token_count = 0;
	token = strtok(input, " ");

	while (token != NULL && *token_count < 64)
	{
		tokens[(*token_count)++] = token;
		token = strtok(NULL, " ");
	}

	tokens[*token_count] = NULL;
}

int is_exit_command(const char *input)
{
	return (strcmp(input, "exit") == 0);
}

int is_printenv_command(const char *input)
{
	return (strcmp(input, "printenv") == 0);
}

void print_prompt(void)
{
	char prompt[] = "$ ";

	write(STDOUT_FILENO, prompt, sizeof(prompt) - 1);
}

ssize_t get_input(char **input, size_t *input_size)
{
	return (getline(input, input_size, stdin));
}

void cleanup(char *input)
{
	free(input);
}
