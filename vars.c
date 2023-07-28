#include "shell.h"

/**
 * is_chain - Determines if the current char in buffer is a chain delimiter
 * @info: Parameter struct
 * @buff: Character buffer
 * @p: Address of the current position in buff.
 *
 * Return: 1 if it is a chain delimiter or 0 otherwise
 */
int is_chain(info_t *info, char *buff, size_t *ptr)
{
    size_t i = *ptr;

    if (buff[i] == '|' && buff[i + 1] == '|')
    {
        buff[i] = 0;
        i++;
        info->cmd_buf_type = CMD_OR;
    }
    else if (buff[i] == '&' && buff[i + 1] == '&')
    {
        buff[i] = 0;
        i++;
        info->cmd_buf_type = CMD_AND;
    }
    else if (buff[i] == ';')
    {
        buff[i] = 0;
        info->cmd_buf_type = CMD_CHAIN;
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
 * @infor: Parameter struct
 * @buff: Character buffer
 * @p: Address of the current position in buff
 * @i: The starting position in buff
 * @len: Length of buff
 *
 * Return: Void
 */
void check_chain(info_t *infor, char *buff, size_t *p, size_t i, size_t len)
{
    size_t k = *p;

    if (infor->cmd_buf_type == CMD_AND)
    {
        if (infor->status)
        {
            buff[i] = 0;
            k = len;
        }
    }

    if (infor->cmd_buf_type == CMD_OR)
    {
        if (!infor->status)
        {
            buff[i] = 0;
            k = len;
        }
    }

    *p = k;
}

/**
 * replace_alias - Replaces an alias in the tokenized string
 * @infor: The parameter struct
 *
 * Return: 1 if replaced or 0 otherwise
 */
int replace_alias(info_t *infor)
{
    int j;
    list_t *node;
    char *ptr;

    for (j = 0; j < 10; j++)
    {
        node = node_starts_with(infor->alias, infor->argv[0], '=');
        if (!node)
            return (0);
        free(infor->argv[0]);
        ptr = _strchr(node->str, '=');
        if (!ptr)
            return (0);
        ptr = _strdup(ptr + 1);
        if (!ptr)
            return (0);
        infor->argv[0] = ptr;
    }
    return (1);
}

/**
 * replace_vars - Replaces variables in the tokenized string
 * @infor: The parameter struct
 *
 * Return: 1 if replaced or 0 otherwise
 */
int replace_vars(info_t *infor)
{
    int j = 0;
    list_t *node;

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

        node = node_starts_with(infor->env, &infor->argv[j][1], '=');
        if (node)
        {
            replace_string(&(infor->argv[j]), _strdup(_strchr(node->str, '=') + 1));
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
 * Return: 1 if replaced or 0 otherwise
 */
int replace_string(char **_old, char *_new)
{
    free(*_old);
    *_old = _new;
    return (1);
}
