#include "shell.h"

/**
 * myerratoi - converts str to int
 * @s: str
 * Return: 0 if no numbers found, else -1
 */

int myerratoi(char *s)
{
	int q = 0;
	unsigned long int result = 0;

	if (*s == '+')
		s++;  /* TODO: why does this make main return 255? */
	for (q = 0;  s[q] != '\0'; q++)
	{
		if (s[q] >= '0' && s[q] <= '9')
		{
			result *= 10;
			result += (s[q] - '0');
			if (result > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (result);
}

/**
 * print_error - displays error msg
 * @info: parameter & return info struct
 * @estr: str containing error.
 * Return: 0 if no numbers found,else -1 on error
 */

void print_error(info_t *info, char *estr)
{
	_eputs(info->fname);
	_eputs(": ");
	print_d(info->line_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(info->argv[0]);
	_eputs(": ");
	_eputs(estr);
}

/**
 * print_d - displays int number to base 10
 * @input: input
 * @fd: filedescriptor
 * Return: amount of char
 */

int print_d(int input, int fd)
{
	int (*__putchar)(char) = _putchar;
	int q, count = 0;
	unsigned int _abs_, current;

	if (fd == STDERR_FILENO)
		__putchar = _eputchar;
	if (input < 0)
	{
		_abs_ = -input;
		__putchar('-');
		count++;
	}
	else
		_abs_ = input;
	current = _abs_;
	for (q = 1000000000; q > 1; q /= 10)
	{
		if (_abs_ / q)
		{
			__putchar('0' + current / q);
			count++;
		}
		current %= q;
	}
	__putchar('0' + current);
	count++;

	return (count);
}

/**
 * convert_number - convert fn, clone of itoa
 * @num: num
 * @base: base
 * @flags: args flags
 * Return: str
 */

char *convert_number(long int num, int base, int flags)
{
	static char *array;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long n = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		n = -num;
		sign = '-';

	}
	array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do	{
		*--ptr = array[n % base];
		n /= base;
	} while (n != 0);

	if (sign)
		*--ptr = sign;
	return (ptr);
}

/**
 * remove_comments - fn replaces  instance of '#' with '\0'
 * @buf: str to modify
 * Return: Always 0;
 */

void remove_comments(char *buf)
{
	int q;

	for (q = 0; buf[q] != '\0'; q++)
		if (buf[q] == '#' && (!q || buf[q - 1] == ' '))
		{
			buf[q] = '\0';
			break;
		}
}
