#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definition of the custom data structure infor_t.
typedef struct infor_t {
    int argc;
    char **argv;
    char **environ;
    // Add any other required members here.
} infor_t;

// Definition of the linked list node.
typedef struct list_t {
    char *str;
    struct list_t *next;
} list_t;

// Function declarations.
void print_list_str(list_t *head);
char *starts_with(const char *str, const char *prefix);
void _eputs(const char *str);
void add_node_end(list_t **head, char *str, int len);

/**
 * print_list_str - Print the strings in the linked list.
 * @head: Pointer to the head of the linked list.
 */
void print_list_str(list_t *head)
{
    list_t *current = head;
    while (current != NULL)
    {
        printf("%s\n", current->str);
        current = current->next;
    }
}

/**
 * starts_with - Check if a string starts with a given prefix.
 * @str: The string to check.
 * @prefix: The prefix to search for.
 * Return: If the string starts with the prefix, return a pointer to the start of the prefix in the string.
 *         Otherwise, return NULL.
 */
char *starts_with(const char *str, const char *prefix)
{
    size_t str_len = strlen(str);
    size_t prefix_len = strlen(prefix);

    if (str_len < prefix_len)
        return NULL;

    if (strncmp(str, prefix, prefix_len) == 0)
        return (char *)str;

    return NULL;
}

/**
 * _eputs - Print an error message to stderr.
 * @str: The error message string to print.
 */
void _eputs(const char *str)
{
    fprintf(stderr, "%s", str);
}

/**
 * add_node_end - Add a new node at the end of the linked list.
 * @head: Pointer to the head of the linked list.
 * @str: The string to be stored in the new node.
 * @len: Length of the string (not used in this placeholder implementation).
 */
void add_node_end(list_t **head, char *str, int len)
{
    list_t *new_node = (list_t *)malloc(sizeof(list_t));
    if (new_node == NULL)
    {
        perror("Error: Unable to allocate memory for new node.");
        exit(EXIT_FAILURE);
    }

    new_node->str = strdup(str);
    new_node->next = NULL;

    if (*head == NULL)
    {
        *head = new_node;
    }
    else
    {
        list_t *current = *head;
        while (current->next != NULL)
        {
            current = current->next;
        }
        current->next = new_node;
    }
}

