#include "shell.h"

/**
 * myputs - displays input str.
 * @str: str
 * Return: void
 */

void myputs(char *str)
{
	int q = 0;

	if (!str)
		return;
	while (str[q] != '\0')
	{
		_eputchar(str[q]);
		q++;
	}
}

/**
 * myputchar - prints char to stderr
 * @c: char
 * Return: success 1.else -1,errno is set.
 */

int myputchar(char c)
{
	static int q;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || q >= WRITE_BUF_SIZE)
	{
		write(2, buf, q);
		q = 0;
	}
	if (c != BUF_FLUSH)
		buf[q++] = c;
	return (1);
}

/**
 * myputfd - prints the char to fd
 * @c: char
 * @fd: filedescriptor
 * Return: succeeds 1.else -1 errno is set.
 */

int myputfd(char c, int fd)
{
	static int q;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || q >= WRITE_BUF_SIZE)
	{
		write(fd, buf, q);
		q = 0;
	}
	if (c != BUF_FLUSH)
		buf[q++] = c;
	return (1);
}

/**
 * myputsfd - displays input str
 * @str: string
 * @fd: filedescriptor
 * Return: amount of chars
 */

int _putsfd(char *str, int fd)
{
	int q = 0;

	if (!str)
		return (0);
	while (*str)
	{
		q += _putfd(*str++, fd);
	}
	return (q);
}

