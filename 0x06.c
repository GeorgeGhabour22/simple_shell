#include "simple.h"

/**
 * error_atoi - Converts a string to an integer with error handling.
 * @s: The string to be converted.
 *
 * Return:
 *	The converted integer on success,
 *	-1 if an error occurs (e.g., non-numeric characters or overflow).
 */
int error_atoi(char *s)
{
	int index = 0;
	unsigned long int r = 0;

	if (*s == '+')
		s++;
	for (index = 0;  s[index] != '\0'; index++)
	{
		if (s[index] >= '0' && s[index] <= '9')
		{
			r *= 10;
			r += (s[index] - '0');
			if (r > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (r);
}

/**
 * error_print - Prints an error message to the standard error output.
 * @info: Pointer to the info_t structure containing shell information.
 * @estr: The error message to be printed.
 *
 * Return: void
 */
void error_print(info_t *info, char *estr)
{
	_eputs(info->fname);
	_eputs(": ");
	decimal_print(info->line_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(info->argv[0]);
	_eputs(": ");
	_eputs(estr);
}

/**
 * decimal_print - Prints an integer in decimal format (BASE 10).
 * @input: The integer to be printed.
 * @fd: The file descriptor to write to (STDOUT_FILENO or STDERR_FILENO).
 *
 * Return:
 *	The number of characters printed.
 */
int decimal_print(int input, int fd)
{
	int (*__putchar)(char) = _putchar;
	int index, count = 0;
	unsigned int _abs_, current;

	if (fd == STDERR_FILENO)
		__putchar = _eputch;
	if (input < 0)
	{
		_abs_ = -input;
		__putchar('-');
		count++;
	}
	else
		_abs_ = input;
	current = _abs_;
	for (index = 1000000000; index > 1; index /= 10)
	{
		if (_abs_ / index)
		{
			__putchar('0' + current / index);
			count++;
		}
		current %= index;
	}
	__putchar('0' + current);
	count++;

	return (count);
}

/**
 * cnv_n - Converts a long int to a string represent. in a specified base.
 * @num: The long integer to be converted.
 * @base: The base for the conversion (e.g., 10 for decimal, 16 for hexa).
 * @flags: Conversion flags, including CONVERT_UNSIGN and CONVERT_LC.
 *
 * Return:
 *	A pointer to the converted string.
 *	The result is stored in a static buffer, so it is not thread-safe.
 */
char *cnv_n(long int num, int base, int flags)
{
	static char *array;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long n = num;

	if (!(flags & CONVERT_UNSIGN) && num < 0)
	{
		n = -num;
		sign = '-';
	}
	array = flags & CONVERT_LC ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do	{
		*--ptr = array[n % base];
		n /= base;
	} while (n != 0);

	if (sign)
		*--ptr = sign;
	return (ptr);
}

/**
 * rm_comm - Removes comments from a str by replacing '#' with '/0'.
 * @buf: The string to be processed.
 *
 * Return: void
 */
void rm_comm(char *buf)
{
	int index;

	for (index = 0; buf[index] != '\0'; index++)
		if (buf[index] == '#' && (!index || buf[index - 1] == ' '))
		{
			buf[index] = '\0';
			break;
		}
}
