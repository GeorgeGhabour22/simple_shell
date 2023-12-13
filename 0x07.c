#include "simple.h"

/**
 * strn_copy - Copies up to n characters from the source string
 *	to the destination string.
 * @dest: The destination string.
 * @src: The source string.
 * @n: The maximum number of characters to copy.
 *
 * Return:
 *	A pointer to the destination string.
 */
char *strn_copy(char *dest, char *src, int n)
{
	int i, j;
	char *s = dest;

	i = 0;
	while (src[i] != '\0' && i < n - 1)
	{
		dest[i] = src[i];
		i++;
	}
	if (i < n)
	{
		j = i;
		while (j < n)
		{
			dest[j] = '\0';
			j++;
		}
	}
	return (s);
}

/**
 **strn_cat - concatenates two strings.
 * @dest: The destination string.
 * @src: The source string.
 * @n: The maximum number of characters to concatenate.
 *
 * Return:
 *	A pointer to the destination string.
 */
char *strn_cat(char *dest, char *src, int n)
{
	int index, x;
	char *s = dest;

	index = 0;
	x = 0;
	while (dest[index] != '\0')
		index++;
	while (src[x] != '\0' && x < n)
	{
		dest[index] = src[x];
		index++;
		x++;
	}
	if (x < n)
		dest[index] = '\0';
	return (s);
}

/**
 * strn_char - Finds first sign of a char in a string up to a null terminator.
 * @s: The string to be searched.
 * @c: The character to search for.
 *
 * Return:
 *	A pointer to the first occurrence of the character in the string,
 *	or NULL if the character is not found.
 */
char *strn_char(char *s, char c)
{
	do {
		if (*s == c)
			return (s);
	} while (*s++ != '\0');

	return (NULL);
}
