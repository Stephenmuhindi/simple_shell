#include <string.h>
#include "main.h"

void tokenizeInput(char *input, char *tokens[], int *token_count);

void tokenizeInput(char *input, char *tokens[], int *token_count)
{
        char *token;

        token = strtok(input, " ");

        while (token != NULL && *token_count < 64)
        {
                tokens[(*token_count)++] = token;

                token = strtok(NULL, " ");
        }

        tokens[*token_count] = NULL;
}
