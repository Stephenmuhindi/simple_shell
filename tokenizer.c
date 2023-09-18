#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include "main.h"

#define MAX_INPUT_SIZE 1024

void tokenizeInput(char *input, char *tokens[], int *token_count);

int executeCommand(char *tokens[]);

int main(void)
{
    char *input = NULL;
    size_t input_size = 0;

    while (1)
    {
        char prompt[] = "$ ";
        write(STDOUT_FILENO, prompt, strlen(prompt));

        ssize_t read_size = getline(&input, &input_size, stdin);

        if (read_size == -1)
        {
            perror("getline");
            exit(EXIT_FAILURE);
        }

        input[read_size - 1] = '\0';

        char *tokens[64];
        int token_count = 0;

        tokenizeInput(input, tokens, &token_count);

        if (token_count > 0)
        {
            executeCommand(tokens);
        }
    }

    free(input);
    return (EXIT_SUCCESS);
}
