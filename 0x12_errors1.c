#include "simple.h"

/**
 * error_atoi - convert string to integer.
 * @s: string to be converted.
 * Return: 0 if no numbers in string, converted number otherwise
 *       -1 on error.
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
 * error_print - prints an error message.
 * @info: the parameter & return info struct.
 * @estr: string containing specified error type
 * Return: 0 if no numbers in string, converted number otherwise
 *        -1 on error.
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
 * decimal_print - function prints decimal (integer) number (base 10).
 * @input: the input.
 * @fd: the filedescriptor to write to.
 *
 * Return: number of characters printed.
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
 * cnv_n - converter function, a clone of itoa
 * @num: number.
 * @base: base.
 * @flags: args flags.
 *
 * Return: string.
 */
char *cnv_n(long int num, int base, int flags)
{
	static char *array;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long n = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		n = -num;
		sign = '-';
	}
	array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
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
 * rm_comm - function replaces first instance of '#' to '\0'.
 * @buf: address of the string to modify.
 *
 * Return: Always 0.
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
