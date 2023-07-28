#include "shell.h"

/**
 * check_interactive_mode - returns true if the shell is in interactive mode
 * @infor: pointer to ShellInfo_t struct
 *
 * Return: 1 if in interactive mode, 0 otherwise
 */
int check_interactive_mode(infor_t *infor)
{
	return (isatty(STDIN_FILENO) && infor->readfd <= 2);
}

/**
 * is_character_delimiter - checks if a character is a delimiter
 * @c: the character to check
 * @delimiter_string: the delimiter string
 * Return: 1 if true, 0 if false
 */
int is_character_delimiter(char c, char *delimiter_string)
{
	while (*delimiter_string)
		if (*delimiter_string++ == c)
			return (1);
	return (0);
}

/**
 * is_alphabetic - checks for alphabetic character
 * @c: The character to input
 * Return: 1 if c is alphabetic, 0 otherwise
 */
int is_alphabetic(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * string_to_integer - converts a str to an int
 * @str: the str to convert
 * Return: 0 if no numbers in the str, the converted number otherwise
 */
int string_to_integer(char *str)
{
	int i, signature = 1, digit_found = 0, result_interger;
	unsigned int result = 0;

	for (i = 0; str[i] != '\0' && digit_found != 2; i++)
	{
		if (str[i] == '-')
			signature *= -1;

		if (str[i] >= '0' && str[i] <= '9')
		{
			digit_found = 1;
			result *= 10;
			result += (str[i] - '0');
		}
		else if (digit_found == 1)
			digit_found = 2;
	}

	if (signature == -1)
		result_interger = -result;
	else
		result_interger = result;

	return (result_interger);
}
