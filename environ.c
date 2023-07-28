#include "shell.h"

/**
 * _myenv - Prints the current environment.
 * @infor: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0.
 */
int _myenv(info_t *infor)
{
	print_list_str(infor->env);
	return (0);
}

/**
 * _getenv - Gets the value of an environment variable.
 * @infor: Structure containing potential arguments. Used to maintain
 * @_name: Environment variable name.
 *
 * Return: The value of the environment variable or NULL if not found.
 */
char *_getenv(info_t *infor, const char *_name)
{
	list_t *_node = infor->env;
	char *ptr;

	while (_node)
	{
		ptr = starts_with(_node->str, _name);
		if (ptr && *ptr)
			return (ptr);
		_node = _node->next;
	}
	return (NULL);
}

/**
 * _mysetenv - Initialize a new environment variable,
 *             or modify an existing one.
 * @infor: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * Return: Always 0.
 */
int _mysetenv(info_t *infor)
{
	if (infor->argc != 3)
	{
		_eputs("Incorrect number of arguements\n");
		return (1);
	}
	if (_setenv(infor, infor->argv[1], infor->argv[2]))
		return (0);
	return (1);
}

/**
 * _myunsetenv - Remove an environment variable.
 * @infor: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * Return: Always 0.
 */
int _myunsetenv(info_t *infor)
{
	int j;

	if (infor->argc == 1)
	{
		_eputs("Too few arguements.\n");
		return (1);
	}
	for (j = 1; j <= infor->argc; j++)
		_unsetenv(infor, infor->argv[j]);

	return (0);
}

/**
 * populate_env_list - Populates the environment linked list.
 * @infor: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0.
 */
int populate_env_list(info_t *infor)
{
	list_t *_node = NULL;
	size_t j;

	for (j = 0; environ[j]; j++)
		add_node_end(&_node, environ[j], 0);
	infor->env = _node;
	return (0);
}
