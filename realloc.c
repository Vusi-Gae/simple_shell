#include "shell.h"

/**
 * _memset - Fills memory with a constant byte.
 * @h: Pointer to the memory area.
 * @f: The byte to fill *s with.
 * @e: The number of bytes to be filled.
 *
 * Return: 'h', a pointer to the memory area 's'.
 */
char *_memset(char *h, char f, unsigned int e)
{
	unsigned int j;

	for (j = 0; j < e; j++)
		h[j] = f;
	return (h);
}

/**
 * ffree - Frees a string of strings.
 * @_pp: The string of strings.
 */
void ffree(char **_pp)
{
	char **aa = _pp;

	if (!_pp)
		return;
	while (*_pp)
		free(*_pp++);
	free(aa);
}

/**
 * _realloc - Reallocates a block of memory.
 * @_ptr: Pointer to the previous malloc'ated block.
 * @_old_size: Byte size of the previous block.
 * @_new_size: Byte size of the new block.
 *
 * Return: Pointer to the reallocated memory block.
 */
void *_realloc(void *_ptr, unsigned int _old_size, unsigned int _new_size)
{
	char *c;

	if (!_ptr)
		return (malloc(_new_size));
	if (!_new_size)
		return (free(_ptr), NULL);
	if (_new_size == _old_size)
		return (_ptr);

	c = malloc(_new_size);
	if (!c)
		return (NULL);

	_old_size = _old_size < _new_size ? _old_size : _new_size;
	while (_old_size--)
		c[_old_size] = ((char *)_ptr)[_old_size];
	free(_ptr);
	return (c);
}
