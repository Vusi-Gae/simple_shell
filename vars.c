#include "shell.h"

/**
 * is_chain - Determines if the current char in buffer is a chain delimiter
 * @infor: The parameter struct
 * @buf: The character buffer
 * @ptr: Address of the current position in buf
 *
 * Return: 1 if it is a chain delimiter, 0 otherwise
 */
int is_chain(info_t *infor, char *buf, size_t *ptr)
{
    size_t i = *ptr;

    if (buf[i] == '|' && buf[i + 1] == '|')
    {
        buf[i] = 0;
        i++;
        infor->cmd_buf_type = CMD_OR;
    }
    else if (buf[i] == '&' && buf[i + 1] == '&')
    {
        buf[i] = 0;
        i++;
        infor->cmd_buf_type = CMD_AND;
    }
    else if (buf[i] == ';')
    {
        buf[i] = 0;
        infor->cmd_buf_type = CMD_CHAIN;
    }
    else
    {
        return (0);
    }

    *ptr = i;
    return (1);
}

/**
 * check_chain - Checks whether we continue chaining based on last status
 * @info: The parameter struct
 * @buf: The character buffer
 * @p: Address of the current position in buf
 * @i: Starting position in buf
 * @len: Length of buf
 *
 * Return: Void
 */
void check_chain(info_t *info, char *buf, size_t *p, size_t i, size_t len)
{
    size_t f = *p;

    if (info->cmd_buf_type == CMD_AND)
    {
        if (info->status)
        {
            buf[i] = 0;
            f = len;
        }
    }

    if (info->cmd_buf_type == CMD_OR)
    {
        if (!info->status)
        {
            buf[i] = 0;
            f = len;
        }
    }

    *p = f;
}

/**
 * replace_alias - Replaces an alias in the tokenized string
 * @info: The parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
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
 * @infor: The parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_vars(info_t *infor)
{
    int j = 0;
    list_t *_node;

    for (j = 0; infor->argv[j]; j++)
    {
        if (infor->argv[j][0] != '$' || !infor->argv[j][1])
            continue;

        if (!_strcmp(infor->argv[j], "$?"))
        {
            replace_string(&(infor->argv[j]), _strdup(convert_number(infor->status, 10, 0)));
            continue;
        }

        if (!_strcmp(infor->argv[j], "$$"))
        {
            replace_string(&(infor->argv[j]), _strdup(convert_number(getpid(), 10, 0)));
            continue;
        }

        _node = node_starts_with(infor->env, &infor->argv[j][1], '=');
        if (_node)
        {
            replace_string(&(infor->argv[j]), _strdup(_strchr(_node->str, '=') + 1));
            continue;
        }

        replace_string(&infor->argv[j], _strdup(""));
    }

    return (0);
}

/**
 * replace_string - Replaces a string
 * @_old: Address of the old string
 * @_new: New string
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_string(char **_old, char *_new)
{
    free(*_old);
    *_old = _new;
    return (1);
}

