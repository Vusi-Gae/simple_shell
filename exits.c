#include "shell.h"

/**
 * _strncpy - Copies a string from tsrc to destination.
 * @destination: The destination string to be copied to.
 * @tsrc: The source string.
 * @num: The number of characters to be copied.
 * Return: A pointer to the concatenated string.
 */
char *_strncpy(char *destination, char *tsrc, int num)
{
	/* p is the index for iterating through tsrc */
	int p, q;
	/* z points to the beginning of the destination string */
	char *z = destination;

	p = 0;
	while (tsrc[p] != '\0' && p < num - 1)
	{
		destination[p] = tsrc[p];
		p++;
	}
	if (p < num)
	{
		/* q is the indx for adding null char if num is greater than tsrc lgth */
		q = p;
		while (q < num)
		{
			destination[q] = '\0';
			q++;
		}
	}
	return (z);
}

/**
 * _strncat - Concatenates two strings.
 * @destination: The first string.
 * @tsrc: The second string.
 * @num: The number of bytes to be maximally used.
 * Return: A pointer to the concatenated string.
 */
char *_strncat(char *destination, char *tsrc, int num)
{
	/* p is the index for iterating through destination */
	int p, q;
	/* z points to the beginning of the destination string */
	char *z = destination;

	p = 0;
	q = 0;
	while (destination[p] != '\0')
		p++;
	while (tsrc[q] != '\0' && q < num)
	{
		destination[p] = tsrc[q];
		p++;
		q++;
	}
	if (q < num)
		destination[p] = '\0';
	return (z);
}

/**
 * _strchr0 - Locates a character in a string.
 * @s: The string to be parsed.
 * @c: The character to look for.
 * Return: A pointer to the memory area s.
 */
char *_strchr0(char *s, char c)
{
	do {
		if (*s == c)
			return (s);
	} while (*s++ != '\0');

	return (NULL);
}
