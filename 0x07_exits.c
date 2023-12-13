#include "simple.h"

/**
 **strn_copy - copies a string.
 *@dest: the destination of the string to be copied to.
 *@src: the source string.
 *@n: the number of characters to be copied.
 *Return: the concatenated string.
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
 *@dest: first string.
 *@src: second string.
 *@n: the number of bytes to be maximally used.
 *Return: the concatenated string.
 */
char *strn_cat(char *dest, char *src, int n)
{
	int i, j;
	char *s = dest;

	i = 0;
	j = 0;
	while (dest[i] != '\0')
		i++;
	while (src[j] != '\0' && j < n)
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	if (j < n)
		dest[i] = '\0';
	return (s);
}

/**
 **strn_char - locate the characters in a string
 *@s: string to be parsed.
 *@c: character to be looking for.
 *Return: (s) a pointer to the memory area s.
 */
char *strn_char(char *s, char c)
{
	do {
		if (*s == c)
			return (s);
	} while (*s++ != '\0');

	return (NULL);
}
