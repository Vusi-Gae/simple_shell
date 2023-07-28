#include "shell.h"

/**
 * add_node - Adds a node to the start of the list.
 * @_head: Address of ptr to head node.
 * @str: Str to be stored in the node.
 * @num: Node index used by history.
 *
 * Return: Pointer to the newly created node or NULL on failure.
 */
list_t *add_node(list_t **_head, const char *str, int num)
{
	list_t *_new_head;

	if (!_head)
		return (NULL);
	_new_head = malloc(sizeof(list_t));
	if (!_new_head)
		return (NULL);
	_memset((void *)_new_head, 0, sizeof(list_t));
	_new_head->num = num;
	if (str)
	{
		_new_head->str = _strdup(str);
		if (!_new_head->str)
		{
			free(_new_head);
			return (NULL);
		}
	}
	_new_head->next = *_head;
	*_head = _new_head;
	return (_new_head);
}

/**
 * add_node_end - Adds a node to the end of the list.
 * @header: Address of ptr to head node.
 * @str: String to be stored in the node.
 * @num: node index used by history
 *
 * Return: Pointer to the newly created node or NULL on failure.
 */
list_t *add_node_end(list_t **header, const char *str, int num)
{
	list_t *_new_node, *_node;

	if (!header)
		return (NULL);

	_node = *header;
	_new_node = malloc(sizeof(list_t));
	if (!_new_node)
		return (NULL);
	_memset((void *)_new_node, 0, sizeof(list_t));
	_new_node->num = num;
	if (str)
	{
		_new_node->str = _strdup(str);
		if (!_new_node->str)
		{
			free(_new_node);
			return (NULL);
		}
	}
	if (_node)
	{
		while (_node->next)
			_node = _node->next;
		_node->next = _new_node;
	}
	else
		*header = _new_node;
	return (_new_node);
}

/**
 * print_list_str - Prints only the str element of a list_t linked list.
 * @p: Pointer to the first node.
 *
 * Return: Number of nodes in the list.
 */
size_t print_list_str(const list_t *p)
{
	size_t j = 0;

	while (p)
	{
		_puts(p->str ? p->str : "(nil)");
		_puts("\n");
		p = p->next;
		j++;
	}
	return (j);
}

/**
 * delete_node_at_index - Deletes node at given index.
 * @header: Address of pointer to the first node.
 * @index: Index of the node to delete.
 *
 * Return: 1 on success, 0 on failure
 */
int delete_node_at_index(list_t **header, unsigned int index)
{
	list_t *_node, *previous_node;
	unsigned int j = 0;

	if (!header || !*header)
		return (0);

	if (!index)
	{
		_node = *header;
		*header = (*header)->next;
		free(_node->str);
		free(_node);
		return (1);
	}
	_node = *header;
	while (_node)
	{
		if (j == index)
		{
			previous_node->next = _node->next;
			free(_node->str);
			free(_node);
			return (1);
		}
		j++;
		previous_node = _node;
		_node = _node->next;
	}
	return (0);
}

/**
 * free_list - Frees all nodes of a list.
 * @header_ptr: Address of pointer to head node
 *
 * Return: void
 */
void free_list(list_t **header_ptr)
{
	list_t *_node, *_next_node, *_head;

	if (!header_ptr || !*header_ptr)
		return;
	_head = *header_ptr;
	_node = _head;
	while (_node)
	{
		_next_node = _node->next;
		free(_node->str);
		free(_node);
		_node = _next_node;
	}
	*header_ptr = NULL;
}
