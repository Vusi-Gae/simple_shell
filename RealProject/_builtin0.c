#include "shell.h"

/**
 * display_history - Displays the history list, one command per line, preceded
 *                   with line numbers starting at 0.
 * @infor: Structure containing potential arguments. Used to maintain
 *         constant function prototype.
 *
 * Return: Always 0
 */
int display_history(infor_t *infor)
{
	print_list(infor->history);
	return (0);
}

/**
 * unset_alias - Unsets an alias by removing it from the alias list.
 * @infor: Structure containing potential arguments. Used to maintain
 *         constant function prototype.
 * @alias_str: The string representing the alias.
 *
 * Return: Always 0 on success, 1 on error
 */
int unset_alias(infor_t *infor, char *alias_str)
{
	char *p, c;
	int ret;

	p = _strchr(alias_str, '=');
	if (!p)
		return (1);
	c = *p;
	*p = 0;
	ret = delete_node_at_index(&(infor->alias),
		get_node_index(infor->alias, node_starts_with(infor->alias, alias_str, -1)));
	*p = c;
	return (ret);
}

/**
 * set_alias - Sets an alias by adding it to the alias list.
 * @infor: Structure containing potential arguments. Used to maintain
 *         constant function prototype.
 * @alias_str: The string representing the alias.
 *
 * Return: Always 0 on success, 1 on error
 */
int set_alias(infor_t *infor, char *alias_str)
{
	char *p;

	p = _strchr(alias_str, '=');
	if (!p)
		return (1);
	if (!*++p)
		return (unset_alias(infor, alias_str));

	unset_alias(infor, alias_str);
	return (add_node_end(&(infor->alias), alias_str, 0) == NULL);
}

/**
 * print_alias - Prints an alias string.
 * @alias_node: The alias node to print.
 *
 * Return: Always 0 on success, 1 on error
 */
int print_alias(list_t *alias_node)
{
	char *p = NULL, *alias_str = NULL;

	if (alias_node)
	{
		p = _strchr(alias_node->str, '=');
		for (alias_str = alias_node->str; alias_str <= p; alias_str++)
			_putchar(*alias_str);
		_putchar('\'');
		_puts(p + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * manage_alias - Manages alias operations (e.g., print or set aliases).
 * @infor: Structure containing potential arguments. Used to maintain
 *         constant function prototype.
 *
 * Return: Always 0
 */
int manage_alias(infor_t *infor)
{
	int i = 0;
	char *p = NULL;
	list_t *node = NULL;

	if (infor->argc == 1)
	{
		node = infor->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; infor->argv[i]; i++)
	{
		p = _strchr(infor->argv[i], '=');
		if (p)
			set_alias(infor, infor->argv[i]);
		else
			print_alias(node_starts_with(infor->alias, infor->argv[i], '='));
	}

	return (0);
}
