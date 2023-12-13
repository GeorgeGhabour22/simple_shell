#include "simple.h"

/**
 * str_len - Return the length of the string.
 * @s: the string whose length to check.
 *
 * Return: integer length of string.
 */
int str_len(char *s)
{
	int index = 0;

	if (!s)
		return (0);

	while (*s++)
		index++;
	return (index);
}

/**
 * str_cmp - performs the comparison of two strings.
 * @s1: first string.
 * @s2: second string.
 *
 * Return: -ve if s1 < s2, +ve if s1 > s2, 0 if s1 == s2
 */
int str_cmp(char *s1, char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}
	if (*s1 == *s2)
		return (0);
	else
		return (*s1 < *s2 ? -1 : 1);
}

/**
 * starts_with - To check if the needle starts with haystack.
 * @haystack: String to search.
 * @needle: Substring to find.
 *
 * Return: Address of next char of haystack or NULL.
 */
char *starts_with(const char *haystack, const char *needle)
{
	while (*needle)
		if (*needle++ != *haystack++)
			return (NULL);
	return ((char *)haystack);
}

/**
 * str_cat - Concatenate two strings.
 * @dest: Destination buffer.
 * @src: the buffer source.
 *
 * Return: Pointer to the destination buffer.
 */
char *str_cat(char *dest, char *src)
{
	char *r = dest;

	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;
	*dest = *src;
	return (r);
}
