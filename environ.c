#include "shell.h"

/**
 * print_infor_t - Prints the current infor_t variables.
 * @infor: Structure containing potential arguments.
 * Return: Always 0
 */
int print_infor_t(infor_t *infor)
{
    print_list_str(infor->informent_list);
    return (0);
}

/**
 * get_infor_t_value - Gets the value of an infor_t variable.
 * @infor: Structure containing potential arguments.
 * @name: The name of the infor_t variable to retrieve.
 * Return: The value of the specified infor_t variable if found, otherwise returns NULL.
 */
char *get_infor_t_value(infor_t *infor, const char *name)
{
    list_t *node = infor->informent_list;
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
 * set_infor_t_variable - Initialize a new infor_t variable or modify an existing one.
 * @infor: Structure containing potential arguments.
 * Return: Always 0 on success, or 1 if the number of arguments is incorrect.
 */
int set_infor_t_variable(infor_t *infor)
{
    if (infor->argc != 3)
    {
        _eputs("Incorrect number of arguments\n");
        return (1);
    }
    if (setenv(infor->argv[1], infor->argv[2], 1) == 0)
        return (0);
    return (1);
}

/**
 * unset_infor_t_variable - Remove an infor_t variable.
 * @infor: Structure containing potential arguments.
 * Return: Always 0
 */
int unset_infor_t_variable(infor_t *infor)
{
    int i;

    if (infor->argc == 1)
    {
        _eputs("Too few arguments.\n");
        return (1);
    }
    for (i = 1; i <= infor->argc; i++)
        unsetenv(infor->argv[i]);

    return (0);
}

/**
 * populate_infor_t_list - Populates the infor_t linked list.
 * @infor: Structure containing potential arguments.
 * Return: Always 0
 */
int populate_infor_t_list(infor_t *infor)
{
    list_t *node = NULL;
    size_t i;

    for (i = 0; infor->environ[i]; i++)
        add_node_end(&node, infor->environ[i], 0);
    infor->informent_list = node;
    return (0);
}

