#include "shell.h"

/**
 * interactive - checks if shell is interactive.
 * @info: &struct
 * Return: 1, else 0
 */

int interactive(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * is_delim - checks for delimeter
 * @c: char
 * @delim: delimeter str
 * Return: 1,else 0
 */

int is_delim(char c, char *delim)
{
	while (*delim)
		if (*delim++ == c)
			return (1);
	return (0);
}

/**
 * _isalpha - loosk for alphabet
 * @c: char input
 * Return: 1,else 0
 */

int _isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * _atoi - converts a str to int
 * @s: str
 * Return: 0 if no int found, else converted number
 */

int _atoi(char *s)
{
	int q, sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (q = 0; s[q] != '\0' && flag != 2; q++)
	{
		if (s[q] == '-')
			sign *= -1;

		if (s[q] >= '0' && s[q] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (s[q] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		output = -result;
	else
		output = result;

	return (output);
}
