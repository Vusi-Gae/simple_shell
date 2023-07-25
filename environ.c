#include "shell.h"

/**
 * print_environment - Prints the current environment variables.
 * @info: Structure containing potential arguments.
 * Return: Always 0
 */
int print_environment(info_t *info)
{
	print_list_str(info->environment_list);
	return (0);
}

/**
 * get_environment_value - Gets the value of an environment variable.
 * @info: Structure containing potential arguments.
 * @name: The name of the environment variable to retrieve.
 * Return: The value of the specified environment variable if found, otherwise returns NULL.
 */
char *get_environment_value(info_t *info, const char *name)
{
	list_t *node = info->environment_list;
	char *value;

	while (node)
	{
		value = starts_with(node->str, name);
		if (value && *value)
			return (value);
		node = node->next;
	}
	return (NULL);
}

/**
 * set_environment_variable - Initialize a new environment variable or modify an existing one.
 * @info: Structure containing potential arguments.
 * Return: Always 0 on success, or 1 if the number of arguments is incorrect.
 */
int set_environment_variable(info_t *info)
{
	if (info->argc != 3)
	{
		_eputs("Incorrect number of arguments\n");
		return (1);
	}
	if (setenv(info->argv[1], info->argv[2], 1) == 0)
		return (0);
	return (1);
}

/**
 * unset_environment_variable - Remove an environment variable.
 * @info: Structure containing potential arguments.
 * Return: Always 0
 */
int unset_environment_variable(info_t *info)
{
	int i;

	if (info->argc == 1)
	{
		_eputs("Too few arguments.\n");
		return (1);
	}
	for (i = 1; i <= info->argc; i++)
		unsetenv(info->argv[i]);

	return (0);
}

/**
 * populate_environment_list - Populates the environment linked list.
 * @info: Structure containing potential arguments.
 * Return: Always 0
 */
int populate_environment_list(info_t *info)
{
	list_t *node = NULL;
	size_t i;

	for (i = 0; info->environ[i]; i++)
		add_node_end(&node, info->environ[i], 0);
	info->environment_list = node;
	return (0);
}
