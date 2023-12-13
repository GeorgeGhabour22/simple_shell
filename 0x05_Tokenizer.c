#include "simple.h"

/**
 * **str_tow - Splits a string into words. Repeat delimiters are IGNORED
 * @str: The input string.
 * @d: The delimiter string.
 * Return: A pointer to an array of strings, or NULL on fail.
 */

char **str_tow(char *str, char *d)
{
	int index, x, y, z, n_words = 0;
	char **p;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!d)
		d = " ";
	for (index = 0; str[index] != '\0'; index++)
		if (!is_delimeter(str[index], d)
		&& (is_delimeter(str[index + 1], d) || !str[index + 1]))
			n_words++;

	if (n_words == 0)
		return (NULL);
	p = malloc((1 + n_words) * sizeof(char *));
	if (!p)
		return (NULL);
	for (index = 0, x = 0; x < n_words; x++)
	{
		while (is_delimeter(str[index], d))
			index++;
		y = 0;
		while (!is_delimeter(str[index + y], d) && str[index + y])
			y++;
		p[x] = malloc((y + 1) * sizeof(char));
		if (!p[x])
		{
			for (y = 0; y < x; y++)
				free(p[y]);
			free(p);
			return (NULL);
		}
		for (z = 0; z < y; z++)
			p[x][z] = str[index++];
		p[x][z] = 0;
	}
	p[x] = NULL;
	return (p);
}
