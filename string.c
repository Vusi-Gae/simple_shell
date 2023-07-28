#include "shell.h"

/**
 * _strlen - Calculates the length of a string.
 * @s: The input string whose length to check.
 * Return: The length of the string as an integer.
 */
int _strlen(char *s)
{
	int j = 0;

	if (!s)
		return (0);

	while (*s++)
		j++;
	return (j);
}

/**
 * _strcmp - Performs lexicographic comparison of two strings.
 * @s1: 1st string to compare.
 * @s2: 2nd string to compare.
 *
 * Return: An integer value less than, equal to, or greater than zero, depending on the
 *		lexicographic order of the two strings.
 *		- Negative value if s1 is lexicographically less than s2.
 *		- Positive value if s1 is lexicographically greater than s2.
 *		- Zero if s1 is lexicographically equal to s2.
 */
int _strcmp(char *s1, char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}
	if (*s1 == *s2)
		return (0);
	else
		return (*s1 < *s2 ? -1 : 1);
}

/**
 * starts_with - Checks if a string starts with a specific substring.
 * @haystack: The string to search within.
 * @needle: The substring to find at the beginning of the haystack.
 *
 * Return: If the `needle` is found at the beginning of the `haystack`,
 *		a pointer to the next character after the match is returned;
 *		otherwise, NULL is returned.
 */
char *starts_with(const char *haystack, const char *needle)
{
	while (*needle)
		if (*needle++ != *haystack++)
			return (NULL);
	return ((char *)haystack);
}

/**
 * _strcat - Concatenates two strings.
 * @dest: The destination buffer where the source string will be appended.
 * @src: The source buffer, containing the string to be appended.
 *
 * Return: A pointer to the destination buffer.
 */
char *_strcat(char *dest, char *src)
{
	char *ret = dest;

	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;
	*dest = *src;
	return (ret);
}
