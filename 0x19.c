#include "simple.h"

/**
 * str_copy - Copy a string.
 * @dest: The destination.
 * @src: The source.
 *
 * Return: Pointer to the destination.
 */
char *str_copy(char *dest, char *src)
{
	int index = 0;

	if (dest == src || src == 0)
		return (dest);
	while (src[index])
	{
		dest[index] = src[index];
		index++;
	}
	dest[index] = 0;
	return (dest);
}

/**
 * str_dupp - Duplicate a string.
 * @str: the string to be duplicated.
 *
 * Return: The pointer to the duplicated string.
 */
char *str_dupp(const char *str)
{
	int l = 0;
	char *r;

	if (str == NULL)
		return (NULL);
	while (*str++)
		l++;
	r = malloc(sizeof(char) * (l + 1));
	if (!r)
		return (NULL);
	for (l++; l--;)
		r[l] = *--str;
	return (r);
}

/**
 *_puts - Print an input string.
 *@str: The string to be printed.
 *
 * Return: Nothing.
 */
void _puts(char *str)
{
	int index = 0;

	if (!str)
		return;
	while (str[index] != '\0')
	{
		_putchar(str[index]);
		index++;
	}
}

/**
 * _putchar - Writes the char c to stdout.
 * @c: The character to be printed.
 *
 * Return: on success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putchar(char c)
{
	static int index;
	static char buff[WR_BUFF_SIZE];

	if (c == BUFF_FLUSH || index >= WR_BUFF_SIZE)
	{
		write(1, buff, index);
		index = 0;
	}
	if (c != BUFF_FLUSH)
		buff[index++] = c;
	return (1);
}
/**
 * str_tow - Tokenizes a string into an array of words based on delimiters.
 * @str: The input string to be tokenized.
 * @d: Delimiters used to identify word boundaries (default is " ").
 *
 * Description:
 *	Splits the input string into individual words based on the specified
 *	delimiters. Allocates memory for an array of strings, each representing
 *	a word in the input string. The last element of the array is set to NULL.
 *
 * Return:
 *	On success, returns a dynamically allocated array of strings.
 *	On failure or if the input string is empty, returns NULL.
 *
 * Note:
 *	The caller is responsible for freeing the allocated memory.
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
