#include "shell.h"

/**
 * _eputs - Prints an input string to stderr.
 * @str: The string to be printed.
 *
 * Return: Nothing.
 */
void _eputs(char *string_to_print)
{
	int index = 0;

	if (!string_to_print)
		return;
	while (string_to_print[index] != '\0')
	{
		_eputchar(string_to_print[index]);
		index++;
	}
}

/**
 * _eputchar - Writes the character c to stderr.
 * @c: The character to print.
 *
 * Return: On success, 1. On error, -1 is returned, and errno is set appropriately.
 */
int _eputchar(char character_to_write)
{
	static int current_index;
	static char buffer[WRITE_BUF_SIZE];

	if (character_to_write == BUF_FLUSH || current_index >= WRITE_BUF_SIZE)
	{
		write(2, buffer, current_index);
		current_index = 0;
	}
	if (character_to_write != BUF_FLUSH)
		buffer[current_index++] = character_to_write;
	return (1);
}

/**
 * _putfd - Writes the character c to the given file descriptor.
 * @c: The character to print.
 * @fd: The file descriptor to write to.
 *
 * Return: On success, 1. On error, -1 is returned, and errno is set appropriately.
 */
int _putfd(char character_to_write, int fd)
{
	static int current_index;
	static char buffer[WRITE_BUF_SIZE];

	if (character_to_write == BUF_FLUSH || current_index >= WRITE_BUF_SIZE)
	{
		write(fd, buffer, current_index);
		current_index = 0;
	}
	if (character_to_write != BUF_FLUSH)
		buffer[current_index++] = character_to_write;
	return (1);
}

/**
 * _putsfd - Prints an input string to the specified file descriptor.
 * @str: The string to be printed.
 * @fd: The file descriptor to write to.
 *
 * Return: The number of characters put.
 */
int _putsfd(char *string_to_print, int fd)
{
	int index = 0;
	int num_chars_put = 0;

	if (!string_to_print)
		return (0);
	while (string_to_print[index])
	{
		num_chars_put += _putfd(string_to_print[index++], fd);
	}
	return (num_chars_put);
}
