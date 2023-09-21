#include "shell.h"

/**
 * bfree - free pointer, NULLs the address
 * @ptr: &pointer
 * Return: 1 else 0.
 */
int bfree(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}
