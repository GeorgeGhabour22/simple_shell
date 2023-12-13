#include "simple.h"

/**
 *_eputs - prints the input string.
 * @str: the string will be printed.
 *
 * Return: Nothing.
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
 * _eputch - write the character c to stderr.
 * @c: The character to be print.
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
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
 * _putfds - writes the character c to given fd
 * @c: The character to print.
 * @fd: The filedescriptor to write to.
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
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
 *_putsfds - prints an input string.
 * @str: the string to be printed.
 * @fd: the filedescriptor to write to
 *
 * Return: the no. of chars put.
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
