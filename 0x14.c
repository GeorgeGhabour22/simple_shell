#include "simple.h"

/**
 * be_free - Frees the allocated memory and sets the pointer to NULL.
 * @ptr: A pointer to the memory to be freed.
 *
 * Description:
 *	Checks if the pointer is not NULL and frees the allocated memory.
 *	After freeing the memory, it sets the pointer to NULL to avoid
 *	dangling pointers.
 *
 * Return:
 *	Returns 1 on successful freeing of memory, 0 otherwise.
 */
int be_free(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}
