#include "shell.h"

/**
 * _erratoi - Converts a string to an integer.
 * @str: The string to be converted.
 * Return: The converted number if successful, otherwise -1 on error.
 */
int _erratoi(char *str)
{
	int index = 0;
	unsigned long int result = 0;

	if (*str == '+')
		str++; /* TODO: why does this make main return 255? */

	for (index = 0; str[index] != '\0'; index++)
	{
		if (str[index] >= '0' && str[index] <= '9')
		{
			result *= 10;
			result += (str[index] - '0');
			if (result > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (result);
}

/**
 * print_error - Prints an error message.
 * @info: Structure containing parameter & return info.
 * @error_type: String containing specified error type.
 * Return: Nothing.
 */
void print_error(info_t *info, char *error_type)
{
	_eputs(info->file_name);
	_eputs(": ");
	print_d(info->line_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(info->argv[0]);
	_eputs(": ");
	_eputs(error_type);
}

/**
 * print_d - Prints a decimal (integer) number (base 10).
 * @input: The input number to print.
 * @fd: The file descriptor to write to.
 * Return: The number of characters printed.
 */
int print_d(int input, int fd)
{
	int (*__putchar)(char) = _putchar;
	int index, count = 0;
	unsigned int absolute_value, current_value;

	if (fd == STDERR_FILENO)
		__putchar = _eputchar;

	if (input < 0)
	{
		absolute_value = -input;
		__putchar('-');
		count++;
	}
	else
		absolute_value = input;

	current_value = absolute_value;

	for (index = 1000000000; index > 1; index /= 10)
	{
		if (absolute_value / index)
		{
			__putchar('0' + current_value / index);
			count++;
		}
		current_value %= index;
	}
	__putchar('0' + current_value);
	count++;

	return (count);
}

/**
 * convert_number - Converter function that converts a number to a specified base.
 * @num: The number to convert.
 * @base: The base to convert the number to.
 * @flags: Argument flags to specify conversion options.
 * Return: A string representing the converted number.
 */
char *convert_number(long int num, int base, int flags)
{
	static char *array;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long converted_num = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		converted_num = -num;
		sign = '-';
	}

	array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do {
		*--ptr = array[converted_num % base];
		converted_num /= base;
	} while (converted_num != 0);

	if (sign)
		*--ptr = sign;
	return (ptr);
}

/**
 * remove_comments - Replaces the first instance of '#' with '\0'.
 * @buf: Address of the string to modify.
 * Return: Nothing.
 */
void remove_comments(char *buf)
{
	int index;

	for (index = 0; buf[index] != '\0'; index++)
	{
		if (buf[index] == '#' && (!index || buf[index - 1] == ' '))
		{
			buf[index] = '\0';
			break;
		}
	}
}
