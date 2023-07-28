#include "shell.h"

/**
 * _myhistory - Displays the history list, one command by line, preceded
 *              with line numbers, starting at 0.
 * @info: Struct containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int _myhistory(info_t *info)
{
	print_list(info->history);
	return (0);
}

/**
 * unset_alias - Unsets an alias from the alias list.
 * @info: Parameter structure
 * @str: Always str alias
 *
 * Return: Always 0 on success, 1 on error
 */
int unset_alias(info_t *info, char *str)
{
	char *q, c;
	int rett;

	q = _strchr(str, '=');
	if (!q)
		return (1);
	c = *q;
	*q = 0;
	rett = delete_node_at_index(&(info->alias),
		get_node_index(info->alias, node_starts_with(info->alias, str, -1)));
	*q = c;
	return (rett);
}

/**
 * set_alias - Sets an alias to string.
 * @info: Parameter structure
 * @str: The string alias.
 *
 * Return: Always 0 on success, 1 on error
 */
int set_alias(info_t *info, char *str)
{
	char *q;

	q = _strchr(str, '=');
	if (!q)
		return (1);
	if (!*++q)
		return (unset_alias(info, str));

	unset_alias(info, str);
	return (add_node_end(&(info->alias), str, 0) == NULL);
}

/**
 * print_alias - Prints an alias string.
 * @node: The alias node.
 *
 * Return: Always 0 on success, 1 on error.
 */
int print_alias(list_t *node)
{
	char *q = NULL, *b = NULL;

	if (node)
	{
		q = _strchr(node->str, '=');
		for (b = node->str; b <= q; b++)
		_putchar(*b);
		_putchar('\'');
		_puts(q + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * _myalias - Mimics the alias builtin (man alias)
 * @info: Struct containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int _myalias(info_t *info)
{
	int j = 0;
	char *q = NULL;
	list_t *_node = NULL;

	if (info->argc == 1)
	{
		_node = info->alias;
		while (_node)
		{
			print_alias(_node);
			_node = _node->next;
		}
		return (0);
	}
	for (j = 1; info->argv[j]; j++)
	{
		q = _strchr(info->argv[j], '=');
		if (q)
			set_alias(info, info->argv[j]);
		else
			print_alias(node_starts_with(info->alias, info->argv[j], '='));
	}

	return (0);
}
