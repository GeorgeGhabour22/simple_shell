#include "simple.h"

/**
 * is_chain - Tests if the current char in the buffer is a chain delimiter.
 * @info: The parameter structure.
 * @buf: The character buffer.
 * @p: address of current position in buf.
 *
 * Return: 1 if chain delimiter, 0 otherwise.
 */
int is_chain(info_t *info, char *buf, size_t *p)
{
	size_t x = *p;

	if (buf[x] == '|' && buf[x + 1] == '|')
	{
		buf[x] = 0;
		x++;
		info->cmd_buf_type = CMD_OR;
	}
	else if (buf[x] == '&' && buf[x + 1] == '&')
	{
		buf[x] = 0;
		x++;
		info->cmd_buf_type = CMD_AND;
	}
	else if (buf[x] == ';') /* command end */
	{
		buf[x] = 0; /* semicolon --> null */
		info->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*p = x;
	return (1);
}

/**
 * check_chain - Checks what should continue chaining based on the last status.
 * @info: The parameter struct.
 * @buf: The character buffer.
 * @p: Address of current position in the buffer.
 *
 * @l: Length of the buffer.
 * @index: the index to check.
 * Return: Void.
 */
void check_chain(info_t *info, char *buf, size_t *p, size_t index, size_t l)
{
	size_t x = *p;

	if (info->cmd_buf_type == CMD_AND)
	{
		if (info->status)
		{
			buf[index] = 0;
			x = l;
		}
	}
	if (info->cmd_buf_type == CMD_OR)
	{
		if (!info->status)
		{
			buf[index] = 0;
			x = l;
		}
	}

	*p = x;
}

/**
 * replace_alias - Replacing an aliases in the tokenized string.
 * @info: The parameter structure.
 *
 * Return: 1 if replaced, 0 if not.
 */
int replace_alias(info_t *info)
{
	int index;
	list_t *node;
	char *p;

	for (index = 0; index < 10; index++)
	{
		node = node_starts_with(info->alias, info->argv[0], '=');
		if (!node)
			return (0);
		free(info->argv[0]);
		p = strn_char(node->str, '=');
		if (!p)
			return (0);
		p = str_dupp(p + 1);
		if (!p)
			return (0);
		info->argv[0] = p;
	}
	return (1);
}

/**
 * replace_vars - Replacing vars in the tokenized string.
 * @info: the parameter structure.
 *
 * Return: 1 if replaced, 0 otherwise.
 */
int replace_vars(info_t *info)
{
	int index = 0;
	list_t *node;

	for (index = 0; info->argv[index]; index++)
	{
		if (info->argv[index][0] != '$' || !info->argv[index][1])
			continue;

		if (!str_cmp(info->argv[index], "$?"))
		{
			replace_string(&(info->argv[index]),
				str_dupp(cnv_n(info->status, 10, 0)));
			continue;
		}
		if (!str_cmp(info->argv[index], "$$"))
		{
			replace_string(&(info->argv[index]),
				str_dupp(cnv_n(getpid(), 10, 0)));
			continue;
		}
		node = node_starts_with(info->env, &info->argv[index][1], '=');
		if (node)
		{
			replace_string(&(info->argv[index]),
				str_dupp(strn_char(node->str, '=') + 1));
			continue;
		}
		replace_string(&info->argv[index], str_dupp(""));

	}
	return (0);
}

/**
 * replace_string - replaces string.
 * @old: address of the old string.
 * @new: new string.
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_string(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}
