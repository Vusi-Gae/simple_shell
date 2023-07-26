#include "shell.h"

/**
 * print_current_environment - prints the current environment variables
 * @infor: Structure containing relevant information.
 * Return: Always 0
 */
int print_current_environment(infor_t *infor)
{
    print_list_str(infor->env);
    return 0;
}

/**
 * get_environment_variable - gets the value of an environment variable
 * @infor: Structure containing relevant information.
 * @name: Name of the environment variable to retrieve.
 * Return: Pointer to the value of the environment variable,
 * or NULL if not found.
 */
char *get_environment_variable(infor_t *infor, const char *name)
{
    list_t *node = infor->env;
    char *value;

    while (node)
    {
        value = starts_with(node->str, name);
        if (value && *value)
            return value;
        node = node->next;
    }
    return NULL;
}

/**
 * set_environment_variable - Initialize a new environment variable
 * or modify an existing one
 * @infor: Structure containing relevant information.
 * Return: Always 0
 */
int set_environment_variable(infor_t *infor)
{
    if (infor->argc != 3)
    {
        _eputs("Incorrect number of arguments\n");
        return 1;
    }
    if (setenv_variable(infor, infor->argv[1], infor->argv[2]))
        return 0;
    return 1;
}

/**
 * unset_environment_variable - Remove an environment variable
 * @infor: Structure containing relevant information.
 * Return: Always 0
 */
int unset_environment_variable(infor_t *infor)
{
    int i;

    if (infor->argc == 1)
    {
        _eputs("Too few arguments.\n");
        return 1;
    }
    for (i = 1; i < infor->argc; i++)
        unsetenv_variable(infor, infor->argv[i]);

    return 0;
}

/**
 * populate_environment_list - populates the environment linked list
 * @infor: Structure containing relevant information.
 * Return: Always 0
 */
int populate_environment_list(infor_t *infor)
{
    list_t *node = NULL;
    size_t i;

    for (i = 0; environ[i]; i++)
        add_node_end(&node, environ[i], 0);
    infor->env = node;
    return 0;
}
