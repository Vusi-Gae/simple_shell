#include "shell.h"

/**
 * _strlen - Calculates the length of a string.
 * @b: The input string whose length to check.
 *
 * Return: The length of the string as an integer.
 */
int _strlen(char *b)
{
	int j = 0;

	if (!b)
		return (0);

	while (*b++)
		j++;
	return (j);
}

/**
 * _strcmp - Performs lexicographic comparison of two strings.
 * @str1: 1st string to compare.
 * @str2: 2nd string to compare.
 *
 * Return: An integer value less than, equal to, or greater than zero, depending on the
 *		lexicographic order of the two strings.
 *		- Negative value if s1 is lexicographically less than s2.
 *		- Positive value if s1 is lexicographically greater than s2.
 *		- Zero if s1 is lexicographically equal to s2.
 */
int _strcmp(char *str1, char *str2)
{
	while (*str1 && *str2)
	{
		if (*str1 != *str2)
			return (*str1 - *str2);
		str1++;
		str2++;
	}
	if (*str1 == *str2)
		return (0);
	else
		return (*str1 < *str2 ? -1 : 1);
}

/**
 * starts_with - Checks if a string starts with a specific substring.
 * @_haystack: The string to search within.
 * @_needle: The substring to find at the beginning of the haystack.
 *
 * Return: If the `needle` is found at the beginning of the `haystack`,
 *		a pointer to the next character after the match is returned;
 *		otherwise, NULL is returned.
 */
char *starts_with(const char *_haystack, const char *_needle)
{
	while (*_needle)
		if (*_needle++ != *_haystack++)
			return (NULL);
	return ((char *)_haystack);
}

/**
 * _strcat - Concatenates two strings.
 * @_dest: The destination buffer where the source string will be appended.
 * @_src: The source buffer, containing the string to be appended.
 *
 * Return: A pointer to the destination buffer.
 */
char *_strcat(char *_dest, char *_src)
{
	char *_ret = _dest;

	while (*_dest)
		_dest++;
	while (*_src)
		*_dest++ = *_src++;
	*_dest = *_src;
	return (_ret);
}
