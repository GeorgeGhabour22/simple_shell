#include "simple.h"

/**
 * z_history - Displays the command history.
 * @info: Pointer to the info_t structure containing shell information.
 *
 * Return: Always returns 0.
 */
int z_history(info_t *info)
{
	print_list(info->history);
	return (0);
}

/**
 * unset_z_alias - Unsets an alias in the shell.
 * @info: Pointer to the info_t structure containing shell information.
 * @str: String representing the alias to be unset.
 *
 * Return:
 *   0 on success (alias unset),
 *   1 if an error occurs or alias not found.
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
 * set_z_alias - Sets or updates an alias in the shell.
 * @info: Pointer to the info_t structure containing shell information.
 * @str: String representing the alias to be set or updated.
 *
 * Return:
 *   0 on success (alias set or updated),
 *   1 if an error occurs.
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
  * @node: Pointer to the list node representing the alias.
 *
 * Return:
 *   0 on success (alias printed),
 *   1 if the alias is NULL.
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
 * z_alias - Displays or manages aliases.
 * @info: Pointer to the info_t structure containing shell information.
 *
 * Return: Always returns 0.
 */
int z_alias(info_t *info)
{
	int index = 0;
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
	for (index = 1; info->argv[index]; index++)
	{
		p = strn_char(info->argv[index], '=');
		if (p)
			set_z_alias(info, info->argv[index]);
		else
			print_z_alias(node_starts_with(info->alias, info->argv[index], '='));
	}

	return (0);
}
