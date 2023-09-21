#include <stdio.h>
#include <unistd.h>

/**
 * main - Entry point
 * Return: Always 0 (Success)
 */
int main(void)
{
	char *message = "Hello, Betty!\n";
	ssize_t len = 13;

	if (write(STDOUT_FILENO, message, len) != len)
	{
		return (1);
	}

	return (0);
}
