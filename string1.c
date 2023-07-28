#include "shell.h"

/**
 * _strcpy - Copies a string from source to destination.
 * @_dest: Destination buffer to store the copied string.
 * @src: Source string to be copied.
 *
 * Return: The pointer to the destination buffer.
 */

char *_strcpy(char *_dest, char *src)
{
	int j = 0;

	if (_dest == src || src == 0)
		return (_dest);
	while (src[j])
	{
		_dest[j] = src[j];
		j++;
	}
	_dest[j] = 0;
	return (_dest);
}

/**
 * _strdup - Duplicates a string.
 * @_str: String to be duplicated.
 *
 * Return: The pointer to the duplicated string or NULL on failure.
 */

char *_strdup(const char *_str)
{
	int length = 0;
	char *_ret;

	if (_str == NULL)
		return (NULL);
	while (*_str++)
		length++;
	_ret = malloc(sizeof(char) * (length + 1));
	if (!_ret)
		return (NULL);
	for (length++; length--;)
		_ret[length] = *--_str;
	return (_ret);
}

/**
 * _puts - Prints an input string to the standard output (stdout).
 * @_str: String to be printed.
 *
 * Return: None.
 */
void _puts(char *_str)
{
	int j = 0;

	if (!_str)
		return;
	while (_str[j] != '\0')
	{
		_putchar(_str[j]);
		j++;
	}
}

/**
 * _putchar - Writes a character to the standard output (stdout).
 * @b: The character to print.
 * Return: On success, the function returns 1.
 * On error -1 is returned, and errno is set appropriately.
 */
int _putchar(char b)
{
	static int j;
	static char buf[WRITE_BUF_SIZE];

	if (b == BUF_FLUSH || j >= WRITE_BUF_SIZE)
	{
		write(1, buf, j);
		j = 0;
	}
	if (b != BUF_FLUSH)
		buf[j++] = b;
	return (1);
}
