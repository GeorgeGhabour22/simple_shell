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
