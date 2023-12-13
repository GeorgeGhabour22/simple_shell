#include "simple.h"

/**
 * list_len - Determine the length of the linked list.
 * @h: Pointer to the first node.
 *
 * Return: the size of the list.
 */
size_t list_len(const list_t *h)
{
	size_t i = 0;

	while (h)
	{
		h = h->next;
		i++;
	}
	return (i);
}

/**
 * list_to_strings - Returns an array of strings of the list in str.
 * @head: pointer to the first node.
 *
 * Return: array of strings.
 */
char **list_to_strings(list_t *head)
{
	list_t *node = head;
	size_t i = list_len(head), j;
	char **strs;
	char *str;

	if (!head || !i)
		return (NULL);
	strs = malloc(sizeof(char *) * (i + 1));
	if (!strs)
		return (NULL);
	for (i = 0; node; node = node->next, i++)
	{
		str = malloc(str_len(node->str) + 1);
		if (!str)
		{
			for (j = 0; j < i; j++)
				free(strs[j]);
			free(strs);
			return (NULL);
		}

		str = str_copy(str, node->str);
		strs[i] = str;
	}
	strs[i] = NULL;
	return (strs);
}


/**
 * print_list - Prints all elements of the list_t linked list.
 * @h: Pointer to the first node.
 *
 * Return: Size of list
 */
size_t print_list(const list_t *h)
{
	size_t index = 0;

	while (h)
	{
		_puts(cnv_n(h->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		index++;
	}
	return (index);
}

/**
 * node_starts_with - Returns the node whose string starts with the prefix.
 * @node: Pointer to list head.
 * @prefix: String to the match.
 * @c: The next character after the prefix to match.
 *
 * Return: Match node or null.
 */
list_t *node_starts_with(list_t *node, char *prefix, char c)
{
	char *p = NULL;

	while (node)
	{
		p = starts_with(node->str, prefix);
		if (p && ((c == -1) || (*p == c)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 * get_node_index - Gets the index of a node.
 * @head: Pointer the list head.
 * @node: Pointer the node.
 *
 * Return: index of node or -1.
 *
 */
ssize_t get_node_index(list_t *head, list_t *node)
{
	size_t i = 0;

	while (head)
	{
		if (head == node)
			return (i);
		head = head->next;
		i++;
	}
	return (-1);
}
