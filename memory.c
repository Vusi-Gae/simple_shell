#include "shell.h"

/**
 * bfree - Frees a pointer and NULLs the address.
 * @p: Address of the pointer to free.
 *
 * Return: 1 if freed otherwise 0.
 */
int bfree(void **p)
{
	/* Check if the pointer is valid and points to allocated memory */
	if (p && *p)
	{
		/* Free the memory block and set the pointer to NULL */
		free(*p);
		*p = NULL;
		return (1);
	}
	return (0);
}
