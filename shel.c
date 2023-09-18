#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_INPUT_SIZE 1024

int main() {
    char *input = NULL;
    size_t input_size = 0;

    while (1) {
        printf("$ ");
        ssize_t read_size = getline(&input, &input_size, stdin);

        if (read_size == -1) {
            perror("getline");
            exit(EXIT_FAILURE);
        }

        // Remove the newline character
        input[read_size - 1] = '\0';

        // Tokenize the input
        char *token;
        char *tokens[64];
        int token_count = 0;
        token = strtok(input, " ");

        while (token != NULL) {
            tokens[token_count] = token;
            token_count++;
            token = strtok(NULL, " ");
        }

        tokens[token_count] = NULL;

        if (token_count > 0) {
            pid_t pid = fork();

            if (pid < 0) {
                perror("fork");
                exit(EXIT_FAILURE);
            } else if (pid == 0) {
                // Child process
                if (execve(tokens[0], tokens, NULL) == -1) {
                    perror("execve");
                    exit(EXIT_FAILURE);
                }
            } else {
                // Parent process
                int status;
                if (wait(&status) == -1) {
                    perror("wait");
                    exit(EXIT_FAILURE);
                }
            }
        }
    }

    // Clean up
    free(input);
    return (0);
}
