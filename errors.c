#include "shell.h"

/**
 * _eputs - Prints an input string to the standard error (stderr).
 * @_str: The string to be printed.
 *
 * Return: Nothing.
 */
void _eputs(char *_str)
{
	int j = 0;

	if (!_str)
		return;
	while (_str[j] != '\0')
	{
		_eputchar(_str[j]);
		j++;
	}
}

/**
 * _eputchar - Writes the character c to the standard error (stderr).
 * @ch: The character to print.
 *
 * Return: On success 1.
 *         On error, -1 is returned, and errno is set appropriately.
 */
int _eputchar(char ch)
{
	static int j;
	static char buf[WRITE_BUF_SIZE];

	if (ch == BUF_FLUSH || j >= WRITE_BUF_SIZE)
	{
		write(2, buf, j);
		j = 0;
	}
	if (ch != BUF_FLUSH)
		buf[j++] = ch;
	return (1);
}

/**
 * _putfd - Writes the character c to the given file descriptor (fd).
 * @ch: The character to print.
 * @fdd: The file descriptor to write to.
 *
 * Return: On success 1.
 *         On error, -1 is returned, and errno is set appropriately.
 */
int _putfd(char ch, int fdd)
{
	static int j;
	static char buf[WRITE_BUF_SIZE];

	if (ch == BUF_FLUSH || j >= WRITE_BUF_SIZE)
	{
		write(fdd, buf, j);
		j = 0;
	}
	if (ch != BUF_FLUSH)
		buf[i++] = ch;
	return (1);
}

/**
 * _putsfd - prints an input string
 * @str: the string to be printed
 * @fd: the filedescriptor to write to
 *
 * Return: the number of chars put
 */
int _putsfd(char *str, int fd)
{
	int i = 0;

	if (!str)
		return (0);
	while (*str)
	{
		i += _putfd(*str++, fd);
	}
	return (i);
}
