#include "simple.h"

/**
 * z_history - display the history list, one command by line, preceded
 *              with line numbers, starting at 0.
 * @info: Structure containing potential args. Used to maintain.
 *        constant function prototype.
 *  Return: Always 0.
 */
int z_history(info_t *info)
{
	print_list(info->history);
	return (0);
}

/**
 * unset_z_alias - sets alias to string.
 * @info: parameter struct.
 * @str: the string alias.
 *
 * Return: Always 0 on success, 1 on error.
 */
int unset_z_alias(info_t *info, char *str)
{
	char *p, c;
	int ret;

	p = strn_char(str, '=');
	if (!p)
		return (1);
	c = *p;
	*p = 0;
	ret = delete_node_at_index(&(info->alias),
		get_node_index(info->alias, node_starts_with(info->alias, str, -1)));
	*p = c;
	return (ret);
}

/**
 * set_z_alias - sets alias to string.
 * @info: parameter struct.
 * @str: the string alias.
 *
 * Return: Always 0 on success, 1 on error
 */
int set_z_alias(info_t *info, char *str)
{
	char *p;
	int r;

	p = strn_char(str, '=');
	if (!p)
		return (1);
	if (!*++p)
	{
		r = unset_z_alias(info, str);
		return (r);
	}

	unset_z_alias(info, str);
	return (add_node_end(&(info->alias), str, 0) == NULL);
}

/**
 * print_z_alias - print an alias string.
 * @node: alias node.
 *
 * Return: Always 0 on success, 1 on error.
 */
int print_z_alias(list_t *node)
{
	char *p = NULL, *a = NULL;

	if (node)
	{
		p = strn_char(node->str, '=');
		for (a = node->str; a <= p; a++)
			_putchar(*a);
		_putchar('\'');
		_puts(p + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * z_alias - mimics the alias built-in (man alias).
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int z_alias(info_t *info)
{
	int i = 0;
	char *p = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			print_z_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; info->argv[i]; i++)
	{
		p = strn_char(info->argv[i], '=');
		if (p)
			set_z_alias(info, info->argv[i]);
		else
			print_z_alias(node_starts_with(info->alias, info->argv[i], '='));
	}

	return (0);
}
