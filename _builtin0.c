#include "shell.h"

/**
 * display_history - displays the history list, one command by line, preceded
 *                   with line numbers, starting at 0.
 * @infor: Structure containing potential arguments. Used to maintain
 *         constant function prototype.
 * Return: Always 0
 */
int display_history(infor_t *infor)
{
	print_list(infor->history);
	return (0);
}

/**
 * unset_alias - unsets alias from the alias list
 * @infor: Parameter struct
 * @alias_str: The string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int unset_alias(infor_t *infor, char *alias_str)
{
	char *equal_ptr, equal_char;
	int ret;

	equal_ptr = _strchr(alias_str, '=');
	if (!equal_ptr)
		return (1);
	equal_char = *equal_ptr;
	*equal_ptr = '\0';
	ret = delete_node_at_index(&(infor->alias),
			get_node_index(infor->alias,
			node_starts_with(infor->alias, alias_str, -1)));
	*equal_ptr = equal_char;
	return (ret);
}

/**
 * set_alias - sets an alias to the alias list
 * @infor: Parameter struct
 * @alias_str: The string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int set_alias(infor_t *infor, char *alias_str)
{
	char *equal_ptr;

	equal_ptr = _strchr(alias_str, '=');
	if (!equal_ptr)
		return (1);
	if (!*++equal_ptr)
		return (unset_alias(infor, alias_str));

	unset_alias(infor, alias_str);
	return (add_node_end(&(infor->alias), alias_str, 0) == NULL);
}

/**
 * print_alias - prints an alias string
 * @alias_node: The alias node
 *
 * Return: Always 0 on success, 1 on error
 */
int print_alias(list_t *alias_node)
{
	char *alias_ptr = NULL, *equal_ptr = NULL;

	if (alias_node)
	{
		equal_ptr = _strchr(alias_node->str, '=');
		for (alias_ptr = alias_node->str; alias_ptr <= equal_ptr; alias_ptr++)
			_putchar(*alias_ptr);
		_putchar('\'');
		_puts(equal_ptr + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * manage_alias - mimics the alias builtin
 * @infor: Structure containing potential arguments. Used to maintain
 *         constant function prototype.
 * Return: Always 0
 */
int manage_alias(infor_t *infor)
{
	int i = 0;
	char *equal_ptr = NULL;
	list_t *alias_node = NULL;

	if (infor->argc == 1)
	{
		alias_node = infor->alias;
		while (alias_node)
		{
			print_alias(alias_node);
			alias_node = alias_node->next;
		}
		return (0);
	}

	for (i = 1; infor->argv[i]; i++)
	{
		equal_ptr = _strchr(infor->argv[i], '=');
		if (equal_ptr)
			set_alias(infor, infor->argv[i]);
		else
			print_alias(node_starts_with(infor->alias, infor->argv[i], '='));
	}

	return (0);
}
