#include "simple.h"

/**
 * is_interactive - returns true if shell is in the interactive mode.
 * @info: struct address.
 * Return: 1 if interactive mode, 0 if not.
 */
int is_interactive(info_t *info)
{
	int isTTY = isatty(STDIN_FILENO);
	int isReadFDValid = (info->readfd <= 2);

	return (isTTY && isReadFDValid);
}

/**
 * is_delimeter - checks if character is a delimeter
 * @c: character check
 * @delim: string delimeter
 * Return: 1 if true, 0 if false
 */
int is_delimeter(char c, char *delim)
{
	while (*delim)
		if (*delim++ == c)
			return (1);
	return (0);
}

/**
 *is_alpha - checks for alphabetic character
 *@c: input character
 *Return: 1 if true, 0 if false
 */

int is_alpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 *_atoi - converts a string to an integer
 *@s: the string to be converted
 *Return: 0 if no numbers in string, converted number otherwise
 */

int _atoi(char *s)
{
	int index, sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (index = 0;  s[index] != '\0' && flag != 2; index++)
	{
		if (s[index] == '-')
			sign *= -1;

		if (s[index] >= '0' && s[index] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (s[index] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
	{
		output = -result;
	}
	else
	{
		output = result;
	}
	return (output);
}
