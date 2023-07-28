#include "shell.h"

/**
 * list_len - Determines length of linked list.
 * @p: Pointer to first node.
 *
 * Return: size of list
 */
size_t list_len(const list_t *p)
{
	size_t j = 0;

	while (p)
	{
		p = p->next;
		j++;
	}
	return (j);
}

/**
 * list_to_strings - Returns an array of strings of list->str.
 * @header: Pointer to first node.
 *
 * Return: array of strings or NULL on failure
 */
char **list_to_strings(list_t *header)
{
	list_t *_node = header;
	size_t f = list_len(header), k;
	char **_strs;
	char *str;

	if (!header || !f)
		return (NULL);
	_strs = malloc(sizeof(char *) * (f + 1));
	if (!_strs)
		return (NULL);
	for (f = 0; _node; _node = _node->next, f++)
	{
		str = malloc(_strlen(_node->str) + 1);
		if (!str)
		{
			for (k = 0; k < f; k++)
				free(_strs[k]);
			free(_strs);
			return (NULL);
		}

		str = _strcpy(str, _node->str);
		_strs[f] = str;
	}
	_strs[f] = NULL;
	return (_strs);
}


/**
 * print_list - Prints all elements of a list_t linked list.
 * @p: Pointer to first node.
 *
 * Return: Size of list
 */
size_t print_list(const list_t *p)
{
	size_t j = 0;

	while (p)
	{
		_puts(convert_number(p->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(p->str ? p->str : "(nil)");
		_puts("\n");
		p = p->next;
		j++;
	}
	return (j);
}

/**
 * node_starts_with - Returns the node whose string starts with a prefix.
 * @f_node: Pointer to the list head.
 * @prefix: String to match.
 * @c: The next character after prefix to match.
 *
 * Return: The matching node or NULL if not found.
 */
list_t *node_starts_with(list_t *f_node, char *prefix, char c)
{
	char *ptr = NULL;

	while (f_node)
	{
		ptr = starts_with(f_node->str, prefix);
		if (ptr && ((c == -1) || (*ptr == c)))
			return (f_node);
		f_node = f_node->next;
	}
	return (NULL);
}

/**
 * get_node_index - Gets the index of a node in the list.
 * @header: Pointer to the list head.
 * @f_node: Pointer to the node.
 *
 * Return: Index of the node or -1 if not found.
 */
ssize_t get_node_index(list_t *header, list_t *f_node)
{
	size_t j = 0;

	while (header)
	{
		if (header == f_node)
			return (j);
		header = header->next;
		j++;
	}
	return (-1);
}
