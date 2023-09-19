#include "shell.h"

void print_command_not_found(const char *command)
{
	char error_message[100];
	snprintf(error_message, sizeof(error_message), "Command not found: %s\n", command);

	write(STDOUT_FILENO, error_message, strlen(error_message));
}
