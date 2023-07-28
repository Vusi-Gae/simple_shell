#include "shell.h"

/**
 * **strtow - Splits a string into words using a delimiter. Repeat delimiters are ignored.
 * @_str: Input string to be split.
 * @d: Delimiter string including characters utilized to split the input string.
 *
 * Return: Pointer to an array of strings containing the split words or NULL on failure.
 */

char **strtow(char *_str, char *d)
{
	int y, j, k, m, num_words = 0;
	char **s;

	if (_str == NULL || _str[0] == 0)
		return (NULL);
	if (!d)
		d = " ";
	for (y = 0; _str[y] != '\0'; y++)
		if (!is_delim(_str[y], d) && (is_delim(_str[y + 1], d) || !_str[y + 1]))
			num_words++;

	if (num_words == 0)
		return (NULL);
	s = malloc((1 + num_words) * sizeof(char *));
	if (!s)
		return (NULL);
	for (y = 0, j = 0; j < num_words; j++)
	{
		while (is_delim(_str[y], d))
			y++;
		k = 0;
		while (!is_delim(_str[y + k], d) && _str[y + k])
			k++;
		s[j] = malloc((k + 1) * sizeof(char));
		if (!s[j])
		{
			for (k = 0; k < j; k++)
				free(s[k]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			s[j][m] = _str[y++];
		s[j][m] = 0;
	}
	s[j] = NULL;
	return (s);
}

/**
 * **strtow2 - Splits a string into words using a single delimiter character.
 * @str: The input string to be split.
 * @dl: The delimiter character used to separate words in the input string.
 *
 * Return: A pointer to an array of strings containing the split words or NULL on failure.
 */
char **strtow2(char *str, char dl)
{
	int i, j, k, m, num_words = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	for (i = 0; str[i] != '\0'; i++)
		if ((str[i] != dl && str[i + 1] == dl) ||
				    (str[i] != dl && !str[i + 1]) || str[i + 1] == dl)
			num_words++;
	if (num_words == 0)
		return (NULL);
	s = malloc((1 + num_words) * sizeof(char *));
	if (!s)
		return (NULL);
	for (i = 0, j = 0; j < num_words; j++)
	{
		while (str[i] == dl && str[i] != dl)
			i++;
		k = 0;
		while (str[i + k] != dl && str[i + k] && str[i + k] != dl)
			k++;
		s[j] = malloc((k + 1) * sizeof(char));
		if (!s[j])
		{
			for (k = 0; k < j; k++)
				free(s[k]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			s[j][m] = str[i++];
		s[j][m] = 0;
	}
	s[j] = NULL;
	return (s);
}
