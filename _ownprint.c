#include "prototypes.h"
/**
 * _ownprint - our own printf
 * @message: string to be printed
 */
void _ownprintf(const char *message)
{
	write(STDOUT_FILENO, message, strlen(message));
}
