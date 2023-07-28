#include "shell.h"

/**
 * get_environ - Returns the string array copy of our environ.
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * Return: Pointer to the environment strings.
 */
char **get_environ(info_t *info)
{
	if (!info->environ || info->env_changed)
	{
		info->environ = list_to_strings(info->env);
		info->env_changed = 0;
	}

	return (info->environ);
}

/**
 * _unsetenv - Remove an environment variable.
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * @var: The string env var property to be removed.
 * Return: 1 on delete, 0 otherwise.
 */
int _unsetenv(info_t *info, char *var)
{
	list_t *_node = info->env;
	size_t j = 0;
	char *ptr;

	if (!_node || !var)
		return (0);

	while (_node)
	{
		ptr = starts_with(_node->str, var);
		if (ptr && *ptr == '=')
		{
			info->env_changed = delete_node_at_index(&(info->env), j);
			j = 0;
			_node = info->env;
			continue;
		}
		_node = _node->next;
		j++;
	}
	return (info->env_changed);
}

/**
 * _setenv - Initialize a new environment variable, or modify an existing one.
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * @var: The string env var property.
 * @value: The string env var value.
 * Return: Always 0.
 */
int _setenv(info_t *info, char *var, char *value)
{
	char *buff = NULL;
	list_t *_node;
	char *ptr;

	if (!var || !value)
		return (0);

	buff = malloc(_strlen(var) + _strlen(value) + 2);
	if (!buff)
		return (1);
	_strcpy(buff, var);
	_strcat(buff, "=");
	_strcat(buff, value);
	_node = info->env;
	while (_node)
	{
		ptr = starts_with(_node->str, var);
		if (ptr && *ptr == '=')
		{
			free(_node->str);
			_node->str = buff;
			info->env_changed = 1;
			return (0);
		}
		_node = _node->next;
	}
	add_node_end(&(info->env), buff, 0);
	free(buff);
	info->env_changed = 1;
	return (0);
}
