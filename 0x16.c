#include "simple.h"

/**
 **_memset - Fill the memory with a constant byte.
 *@s: The pointer into the memory area.
 *@b: The byte to fill *s with.
 *@n: The number of bytes to be filled.
 *Return: (s) A pointer to the memory area s.
 */
char *_memset(char *s, char b, unsigned int n)
{
	unsigned int index;

	for (index = 0; index < n; index++)
		s[index] = b;
	return (s);
}

/**
 * ffree - free the string of strings.
 * @pp: string of strings.
 */
void ffree(char **pp)
{
	char **x = pp;

	if (!pp)
		return;
	while (*pp)
		free(*pp++);
	free(x);
}

/**
 * _realloc - Reallocating a block of memory.
 * @ptr: Pointer to the previous block that was malloced.
 * @old_size: the size of the old block
 * @new_size: size of new block
 *
 * Return: pointer to reallocated memory block.
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *new_ptr;

	if (!ptr)
		return (malloc(new_size));
	if (!new_size)
	{
		free(ptr);
		return (NULL);
	}
	if (new_size == old_size)
		return (ptr);

	new_ptr = malloc(new_size);
	if (!new_ptr)
		return (NULL);

	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		new_ptr[old_size] = ((char *)ptr)[old_size];
	free(ptr);
	return (new_ptr);
}
