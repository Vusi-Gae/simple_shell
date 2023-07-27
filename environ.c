#include "shell.h"

/**
 * _aputs - Prints a string to stderr.
 * @str: The string to be printed.
 *
 * Return: Nothing.
 */
void _aputs(const char *str)
{
	if (!str)
		return;

	while (*str)
		_eputchar(*str++);
}

/**
 * _aputchar - Writes a character to stderr.
 * @c: The character to print.
 *
 * Return: On success, 1. On error, -1 is returned,
 * and errno is set appropriately.
 */
int _aputchar(char c)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(2, buf, i);
		i = 0;
	}

	if (c != BUF_FLUSH)
		buf[i++] = c;

	return (1);
}

/**
 * _eputfd - Writes a character to the given file descriptor.
 * @c: The character to print.
 * @fd: The file descriptor to write to.
 *
 * Return: On success, 1. On error, -1 is returned,
 * and errno is set appropriately.
 */
int _eputfd(char c, int fd)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(fd, buf, i);
		i = 0;
	}

	if (c != BUF_FLUSH)
		buf[i++] = c;

	return (1);
}

/**
 * _eputsfd - Prints a string to the given file descriptor.
 * @str: The string to be printed.
 * @fd: The file descriptor to write to.
 *
 * Return: The number of characters written.
 */
int _eputsfd(char *str, int fd)
{
	int count = 0;

	if (!str)
		return (0);

	while (*str)
	{
		count += _putfd(*str++, fd);
	}

	return (count);
}
