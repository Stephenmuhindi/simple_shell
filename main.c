/**
 * main - where the functions are called
 * Return: always 0
 */
#include "shell.h"

int main(void)
{
	char *input = NULL;
	size_t input_size = 0;
	char *tokens[64];
	int token_count = 0;

	while (1)
	{
		print_prompt();

		if (get_input(&input, &input_size) == -1)
		{
			perror("getline");
			exit(EXIT_FAILURE);
		}

		input[strlen(input) - 1] = '\0';

		if (is_exit_command(input))
		{
			cleanup(input);
			return (EXIT_SUCCESS);
		}

		if (is_printenv_command(input))
		{
			print_env();
		} else
		{
			tokenize_input(input, tokens, &token_count);

			if (token_count > 0)
			{
				execute_command(tokens);
			}
		}
	}

	cleanup(input);
	return (EXIT_SUCCESS);
}
