#include "simple.h"

/**
 * gett_environ - Return the string array copied from environment.
 * @info: Pointer to the info_t structure containing shell information.
 *
 * Description:
 *	If the environment variables have changed or are not initialized,
 *	it converts the linked list of environment variables to an array of strings.
 *
 * Return:
 *	A pointer to the array of environment variables.
 */
char **gett_environ(info_t *info)
{
	if (!info->environ || info->env_changed)
	{
		info->environ = list_to_strings(info->env);
		info->env_changed = 0;
	}

	return (info->environ);
}

/**
 * un_setenv - Removes an environ. var. from the shell's environment.
 * @info: Pointer to the info_t structure containing shell information.
 * @var: The name of the environment variable to be removed.
 *
 * Description:
 *	Searches for the specified environ. var. and removes it from the list.
 *
 * Return:
 *	1 if the environment variable is successfully removed,
 *	0 if the variable is not found or if there are errors.
 */
int un_setenv(info_t *info, char *var)
{
	list_t *node = info->env;
	size_t i = 0;
	char *p;

	if (!node || !var)
		return (0);

	while (node)
	{
		p = starts_with(node->str, var);
		if (p && *p == '=')
		{
			info->env_changed = delete_node_at_index(&(info->env), i);
			i = 0;
			node = info->env;
			continue;
		}
		node = node->next;
		i++;
	}
	return (info->env_changed);
}

/**
 * sett_env - initialize a new environ. var,
 *	or modify the existing
 * @info: Pointer to the info_t structure containing shell information.
 * @var: The name of the environment variable.
 * @value: The value to assign to the environment variable.
 *
 * Description:
 *	Creates or updates the specified environment variable with the given value.
 *	If the variable already exists, its value is updated; otherwise, a new
 *	environment variable is created.
 *
 * Return:
 *	0 on success, 1 on memory allocation failure.
 */
int sett_env(info_t *info, char *var, char *value)
{
	char *buf = NULL;
	list_t *node;
	char *p;

	if (!var || !value)
		return (0);

	buf = malloc(str_len(var) + str_len(value) + 2);
	if (!buf)
		return (1);
	str_copy(buf, var);
	str_cat(buf, "=");
	str_cat(buf, value);
	node = info->env;
	while (node)
	{
		p = starts_with(node->str, var);
		if (p && *p == '=')
		{
			free(node->str);
			node->str = buf;
			info->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	add_node_end(&(info->env), buf, 0);
	free(buf);
	info->env_changed = 1;
	return (0);
}
