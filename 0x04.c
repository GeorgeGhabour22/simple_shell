#include "simple.h"

/**
 * z_env - Displays the current environment variables.
 * @info: Pointer to the info_t structure containing shell information.
 *
 * Return: Always returns 0.
 */
int z_env(info_t *info)
{
	print_list_str(info->env);
	return (0);
}

/**
 * get_env - Retrieves the value of an environment variable.
 * @info: Pointer to the info_t structure containing shell information.
 * @name: The name of the environment variable.
 *
 * Return:
 *	A pointer to the value of the environment variable if found,
 *	NULL if the environment variable is not found.
 */
char *get_env(info_t *info, const char *name)
{
	list_t *node = info->env;
	char *ptr;

	while (node)
	{
		ptr = starts_with(node->str, name);
		if (ptr && *ptr)
			return (ptr);
		node = node->next;
	}
	return (NULL);
}

/**
 * set_env - Sets or updates an environment variable.
 * @info: Pointer to the info_t structure containing shell information.
 *
 * Return:
 *	0 on success (environment variable set or updated),
 *	1 if an error occurs (incorrect number of arguments).
 */
int set_env(info_t *info)
{
	if (info->argc != 3)
	{
		_eputs("Incorrect number of arguements\n");
		return (1);
	}
	if (sett_env(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 * unset_env - Unsets one or more environment variables.
 * @info: Pointer to the info_t structure containing shell information.
 *
 * Return:
 *	0 on success (environment variables unset),
 *	1 if an error occurs (too few arguments).
 */
int unset_env(info_t *info)
{
	int index;

	if (info->argc == 1)
	{
		_eputs("Too few arguements.\n");
		return (1);
	}
	for (index = 1; index <= info->argc; index++)
		un_setenv(info, info->argv[index]);

	return (0);
}

/**
 * inhabit_env_list - inhabits environ. linked lists.
 * @info: Pointer to the info_t structure containing shell information.
 *
 * Return: Always returns 0.
 */
int inhabit_env_list(info_t *info)
{
	list_t *node = NULL;
	size_t index;

	for (index = 0; environ[index]; index++)
		add_node_end(&node, environ[index], 0);
	info->env = node;
	return (0);
}
