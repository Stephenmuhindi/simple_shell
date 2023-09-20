#include "shell.h"

/**
 **mystrncpy - copy str
 *@dest: destination str
 *@src: original str
 *@n: amount of bytes
 *Return: worked on str
 */

char *mystrncpy(char *dest, char *src, int n)
{
	int x, y;
	char *s = dest;

	x = 0;
	while (src[x] != '\0' && x < n - 1)
	{
		dest[x] = src[x];
		x++;
	}
	if (x < n)
	{
		y = x;
		while (y < n)
		{
			dest[y] = '\0';
			y++;
		}
	}
	return (s);
}

/**
 **mystrncat - combines two str
 *@dest: str 1
 *@src: str 2
 *@n: max chars used
 *Return: the combined str
 */

char *mystrncat(char *dest, char *src, int n)
{
	int x, y;
	char *s = dest;

	x = 0;
	y = 0;
	while (dest[x] != '\0')
		x++;
	while (src[y] != '\0' && y < n)
	{
		dest[x] = src[y];
		x++;
		y++;
	}
	if (y < n)
		dest[x] = '\0';
	return (s);
}

/**
 **mystrchr - locates char
 *@s: str
 *@c: char
 *Return: pointer to the memory area s
 */

char *_strchr(char *s, char c)
{
	do {
		if (*s == c)
			return (s);
	} while (*s++ != '\0');

	return (NULL);
}
