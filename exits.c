#include "shell.h"

/**
 * _strncpy - Copies a string up to n characters.
 * @dest: The destination string to be copied to.
 * @src: The source string.
 * @n: The number of characters to be copied.
 *
 * Return: The pointer to the destination string.
 */
char *_strncpy(char *dest, char *src, int n)
{
	int b, t;
	char *z = dest;

	b = 0;
	while (src[b] != '\0' && b < n - 1)
	{
		dest[b] = src[b];
		b++;
	}
	if (b < n)
	{
		t = b;
		while (t < n)
		{
			dest[t] = '\0';
			t++;
		}
	}
	return (z);
}

/**
 * _strncat - Concatenates two strings, up to n bytes from the source.
 * @dest: The first string.
 * @src: The second string.
 * @n: The maximum number of bytes to be used.
 *
 * Return: The pointer to the destination string.
 */
char *_strncat(char *dest, char *src, int n)
{
	int b, t;
	char *z = dest;

	b = 0;
	t = 0;
	while (dest[b] != '\0')
		b++;
	while (src[t] != '\0' && t < n)
	{
		dest[b] = src[t];
		b++;
		t++;
	}
	if (t < n)
		dest[b] = '\0';
	return (z);
}

/**
 * _strchr - Locates a character in a string.
 * @s: The string to be parsed.
 * @c: The character to look for.
 *
 * Return: A pointer to the first occurrence of the character c in the string s,
 *         or NULL if the character is not found.
 */
char *_strchr(char *s, char c)
{
	do {
		if (*s == c)
			return (s);
	} while (*s++ != '\0');

	return (NULL);
}
