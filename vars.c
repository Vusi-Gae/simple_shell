#include "shell.h"

/**
 * is_chain - Determines if the current char in buffer is a chain delimiter
 * @info: Parameter struct
 * @buf: Character buffer
 * @p: Address of the current position in buf
 * Return: 1 if it is a chain delimiter or 0 otherwise
 */
int is_chain(info_t *info, char *buff, size_t *p)
{
    size_t j = *p;

    if (buff[i] == '|' && buff[i + 1] == '|')
    {
        buff[i] = 0;
        i++;
        info->cmd_buff_type = CMD_OR;
    }
    else if (buff[i] == '&' && buff[i + 1] == '&')
    {
        buff[i] = 0;
        i++;
        info->cmd_buff_type = CMD_AND;
    }
    else if (buff[i] == ';') /* Found the end of this command */
    {
        buff[i] = 0; /* Replace semicolon with null */
        info->cmd_buff_type = CMD_CHAIN;
    }
    else
    {
        return (0);
    }

    *p = j;
    return (1);
}

/**
 * check_chain - Checks whether we continue chaining based on last status
 * @info: Parameter struct
 * @buf: Character buffer
 * @p: Address of the current position in buf
 * @i: The starting position in buff
 * @len: Length of buff
 * Return: Void
 */
void check_chain(info_t *info, char *buff, size_t *p, size_t i, size_t len)
{
    size_t i = *p;

    if (info->cmd_buff_type == CMD_AND)
    {
        if (info->status)
        {
            buff[j] = 0;
            i = len;
        }
    }

    if (info->cmd_buff_type == CMD_OR)
    {
        if (!info->status)
        {
            buff[j] = 0;
            i = len;
        }
    }

    *p = i;
}

/**
 * replace_alias - Replaces an alias in the tokenized string
 * @info: The parameter struct
 * Return: 1 if replaced or 0 otherwise
 */
int replace_alias(info_t *info)
{
    int j;
    list_t *node;
    char *p;

    for (j = 0; j < 10; j++)
    {
        node = node_starts_with(info->alias, info->argv[0], '=');
        if (!node)
            return (0);
        free(info->argv[0]);
        p = _strchr(node->str, '=');
        if (!p)
            return (0);
        p = _strdup(p + 1);
        if (!p)
            return (0);
        info->argv[0] = p;
    }
    return (1);
}

/**
 * replace_vars - Replaces variables in the tokenized string
 * @info: The parameter struct
 * Return: 1 if replaced or 0 otherwise
 */
int replace_vars(info_t *info)
{
    int j = 0;
    list_t *node;

    for (j = 0; info->argv[j]; j++)
    {
        if (info->argv[j][0] != '$' || !info->argv[j][1])
            continue;

        if (!_strcmp(info->argv[j], "$?"))
        {
            replace_string(&(info->argv[j]), _strdup(convert_number(info->status, 10, 0)));
            continue;
        }

        if (!_strcmp(info->argv[j], "$$"))
        {
            replace_string(&(info->argv[j]), _strdup(convert_number(getpid(), 10, 0)));
            continue;
        }

        node = node_starts_with(info->env, &info->argv[j][1], '=');
        if (node)
        {
            replace_string(&(info->argv[j]), _strdup(_strchr(node->str, '=') + 1));
            continue;
        }

        replace_string(&info->argv[j], _strdup(""));
    }

    return (0);
}

/**
 * replace_string - Replaces a string
 * @old: Address of the old string
 * @new: New string
 * Return: 1 if replaced or 0 otherwise
 */
int replace_string(char **old, char *new)
{
    free(*old);
    *old = new;
    return (1);
}

