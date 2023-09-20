#include "shell.h"

/**
 * afree - free pointer and NULLs address
 * @ptr: &pointer
 * Return: 1 else 0.
 */
int afree(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}
