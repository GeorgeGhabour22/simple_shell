#include "simple.h"

/**
 * _eputs - Prints a string to the standard error output.
 * @str: The string to be printed.
 *
 * Return: void
 */
void _eputs(char *str)
{
	int index = 0;

	if (!str)
		return;
	while (str[index] != '\0')
	{
		_eputch(str[index]);
		index++;
	}
}

/**
 * _eputch - Writes a character to the standard error output.
 * @c: The character to be written.
 *
 * Return:
 *	1 on success,
 *	0 on failure.
 */
int _eputch(char c)
{
	static int index;
	static char buf[WR_BUFF_SIZE];

	if (c == BUFF_FLUSH || index >= WR_BUFF_SIZE)
	{
		write(2, buf, index);
		index = 0;
	}
	if (c != BUFF_FLUSH)
		buf[index++] = c;
	return (1);
}

/**
 * _putfds - Writes a character to the specified file descriptor.
 * @c: The character to be written.
 * @fd: The file descriptor to write to.
 *
 * Return:
 *	1 on success,
 *	0 on failure.
 */
int _putfds(char c, int fd)
{
	static int index;
	static char buf[WR_BUFF_SIZE];

	if (c == BUFF_FLUSH || index >= WR_BUFF_SIZE)
	{
		write(fd, buf, index);
		index = 0;
	}
	if (c != BUFF_FLUSH)
		buf[index++] = c;
	return (1);
}

/**
 * _putsfds - Writes a string to the specified file descriptor.
 * @str: The string to be written.
 * @fd: The file descriptor to write to.
 *
 * Return:
 *	The number of characters written on success,
 *	0 if the string is NULL or on failure.
 */
int _putsfds(char *str, int fd)
{
	int index = 0;

	if (!str)
		return (0);
	while (*str)
	{
		index += _putfds(*str++, fd);
	}
	return (index);
}
