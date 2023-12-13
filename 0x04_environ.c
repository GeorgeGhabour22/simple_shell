#include "simple.h"

/**
 * z_env - print the current environment.
 * @info: Structure containing potential args. Used to maintain
 *          constant function prototype.
 * Return: Always 0.
 */
int z_env(info_t *info)
{
	print_list_str(info->env);
	return (0);
}

/**
 * get_env - get value of an environ variable.
 * @info: Structure containing potential args. Used to maintain
 * @name: env var name.
 *
 * Return: the value.
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
 * set_env - Initialize a new environment variable,
 *             or modify an existing one
 * @info: Structure containing potential args. Used to maintain
 *        constant function prototype.
 *  Return: Always 0.
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
 * unset_env - Remove the environment variable.
 * @info: Structure containing potential args. Used to maintain
 *        constant function prototype.
 *  Return: Always 0.
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
 * inhabit_env_list - inhabits env linked lists.
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0.
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
