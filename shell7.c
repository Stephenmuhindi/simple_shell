#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

extern char **environ; /* Declare environ */

#define MAX_INPUT_LENGTH 1024
#define MAX_TOKENS 10

/* Function to parse the command line into tokens */
int parse_command(char *input, char *tokens[]) {
    int token_count = 0;
    char *token = strtok(input, " \t\n");

    while (token != NULL && token_count < MAX_TOKENS) {
        tokens[token_count] = token;
        token_count++;
        token = strtok(NULL, " \t\n");
    }

    tokens[token_count] = NULL; /* Add a NULL pointer as the last token */
    return token_count;
}

/* Function to execute a command */
int execute_command(char *tokens[]) {
    int status;
    pid_t pid; /* Declare pid here */

    /* Check if the command exists */
    if (access(tokens[0], X_OK) == -1) {
        perror("Command not found");
        return 1;
    }

    pid = fork(); /* Initialize pid here */

    if (pid < 0) {
        perror("Fork failed");
        return 1;
    }

    if (pid == 0) { /* Child process */
        /* Check for built-in commands */
        if (strcmp(tokens[0], "exit") == 0) {
            exit(0); /* Exit the shell gracefully */
        } else if (strcmp(tokens[0], "cd") == 0) {
            if (tokens[1] != NULL) {
                if (chdir(tokens[1]) != 0) {
                    perror("cd");
                    exit(1);
                }
            }
            exit(0);
        } else if (strcmp(tokens[0], "env") == 0) {
            /* Print the current environment */
            char **env = environ;
            while (*env != NULL) {
                printf("%s\n", *env);
                env++;
            }
            exit(0);
        }

        /* Execute other commands using execvp */
        if (execvp(tokens[0], tokens) == -1) {
            perror("Command not found");
            exit(1);
        }
    } else { /* Parent process */
        waitpid(pid, &status, 0);
        return WEXITSTATUS(status);
    }
    return 0;
}

int main() {
    char input[MAX_INPUT_LENGTH];
    char *tokens[MAX_TOKENS];
    int token_count;

    while (1) {
        if (write(STDOUT_FILENO, "shell> ", 7) == -1) {
            perror("Write failed");
            return 1;
        }
        if (fgets(input, sizeof(input), stdin) == NULL) {
            if (write(STDOUT_FILENO, "\n", 1) == -1) {
                perror("Write failed");
                return 1;
            }
            break; /* End of file (Ctrl+D) or error */
        }

        token_count = parse_command(input, tokens);

        if (token_count > 0) {
            int result = execute_command(tokens);

            if (result != 0) {
                char error_msg[64];
                snprintf(error_msg, sizeof(error_msg), "Command failed with exit code %d\n", result);
                if (write(STDERR_FILENO, error_msg, strlen(error_msg)) == -1) {
                    perror("Write failed");
                    return 1;
                }
            }
        }
    }

    return 0;
}
