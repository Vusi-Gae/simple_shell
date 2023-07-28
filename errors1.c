#include "shell.h"

/**
 * _erratoi - converts a string to an integer.
 * @t: the string to be converted.
 * Return: The converted integer value if the string contains valid numbers,
 *         0 if no numbers are found in the string,
 *         -1 on error (e.g. when the string is not a valid integer).
 */
int _erratoi(char *t)
{
	int j = 0;
	unsigned long int res = 0;

	if (*t == '+')
		t++;
	for (j = 0;  t[j] != '\0'; j++)
	{
		if (t[j] >= '0' && t[j] <= '9')
		{
			res *= 10;
			res += (t[j] - '0');
			if (res > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (res);
}

/**
 * print_error - Prints an error message based on the specified error type.
 * @infor: A pointer to the parameter and return info struct.
 * @_estr: The string containing the specified error type.
 *
 * Function prints an error message to the standard error stream based on the
 * error type specified in the input string @estr.
 *
 * Return: The function does not have a return value (void).
 */
void print_error(info_t *infor, char *_estr)
{
	_eputs(infor->fname);
	_eputs(": ");
	print_d(infor->line_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(infor->argv[0]);
	_eputs(": ");
	_eputs(_estr);
}

/**
 * print_d - Prints a decimal (integer) number (base 10).
 * @input: The integer number to be printed.
 * @ffd: The file descriptor to write the output to.
 *
 * Function prints the deci representation of the input integer number @input
 * to the specified file descriptor @fd.
 *
 * Return: The number of characters printed as an integer.
 */
int print_d(int input, int ffd)
{
	int (*__putchar)(char) = _putchar;
	int j, count = 0;
	unsigned int _abs_, current;

	if (ffd == STDERR_FILENO)
		__putchar = _eputchar;
	if (input < 0)
	{
		_abs_ = -input;
		__putchar('-');
		count++;
	}
	else
		_abs_ = input;
	current = _abs_;
	for (j = 1000000000; j > 1; j /= 10)
	{
		if (_abs_ / j)
		{
			__putchar('0' + current / j);
			count++;
		}
		current %= j;
	}
	__putchar('0' + current);
	count++;

	return (count);
}

/**
 * convert_number - Converts a given num to a str representation in a specified base.
 * @_num: The number to be converted.
 * @_base: The base to which the number will be converted
 * @flag: Flags or arguments for special formatting
 *
 * Return: A string representation of the converted number is returned.
 */
char *convert_number(long int _num, int _base, int flag)
{
	static char *array;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long n = _num;

	if (!(flag & CONVERT_UNSIGNED) && _num < 0)
	{
		n = -_num;
		sign = '-';

	}
	array = flag & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do	{
		*--ptr = array[n % _base];
		n /= _base;
	} while (n != 0);

	if (sign)
		*--ptr = sign;
	return (ptr);
}

/**
 * remove_comments - function replaces first instance of '#' with '\0'
 * @buff: The address of the string to modify
 *
 * Return: Always returns 0.
 */
void remove_comments(char *buff)
{
	int j;

	for (j = 0; buff[j] != '\0'; j++)
		if (buff[j] == '#' && (!j || buff[j - 1] == ' '))
		{
			buff[j] = '\0';
			break;
		}
}
