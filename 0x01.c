#include "simple.h"

/**
 * is_interactive - Checks if program is running in interactive mode.
 * @info: Pointer to the info_t structure containing shell information.
 *
 * Return: 1 if in interactive mode, 0 otherwise.
 */
int is_interactive(info_t *info)
{
	int isTTY = isatty(STDIN_FILENO);
	int isReadFDValid = (info->readfd <= 2);

	return (isTTY && isReadFDValid);
}

/**
 * is_delimeter - Checks if a character is a delimiter.
 * @c: The character to be checked.
 * @delim: A string containing the delimiters to check against.
 *
 * Return: 1 if the character is a delimiter, 0 otherwise.
 */
int is_delimeter(char c, char *delim)
{
	while (*delim)
		if (*delim++ == c)
			return (1);
	return (0);
}

/**
 * is_alpha - Checks if a character is an alphabetic character.
 * @c: The character to be checked.
 *
 * Return: 1 if the character is an alphabetic character, 0 otherwise.
 */
int is_alpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * _atoi - Converts a string to an integer.
 * @s: The string to be converted.
 *
 * Return: The converted integer.
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
