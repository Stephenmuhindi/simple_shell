#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <errno.h>

#define MAX_INPUT_SIZE 1024
#define STDOUT_FILENO 1

void fileSearchAndDisplay(int argc, char *argv[]);
void tokenize_input(char *input, char *tokens[], int *token_count);
int execute_command(char *tokens[]);
int is_exit_command(const char *input);
int is_printenv_command(const char *input);
void print_prompt(void);
ssize_t get_input(char **input, size_t *input_size);
void cleanup(char *input);
void print_env(void);
void print_command_not_found(const char *command);
void printPathDirectories();

#endif /* SHELL_H */
