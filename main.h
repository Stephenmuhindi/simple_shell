#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <string.h>

void tokenizeInput(char *input, char *tokens[], int *token_count);
int executeCommand(char *tokens[]);
int executeCommand(char *tokens[]);
void tokenizeInput(char *input, char *tokens[], int *token_count);

#endif
