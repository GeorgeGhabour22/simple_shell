#include "simple.h"

/**
 * clear_inf - Clears the fields of the info_t structure.
 * @info: Pointer to the info_t structure to be cleared.
 *
 * Description:
 *`Resets the fields of the info_t structure to their initial values.
 *
 * Return: Void.
 */
void clear_inf(info_t *info)
{
	info->arg = NULL;
	info->argv = NULL;
	info->path = NULL;
	info->argc = 0;
}

/**
 * set_inf - Initializes fields of the info_t structure with command-line args.
 * @info: Pointer to the info_t structure to be initialized.
 * @av: The command-line arguments array from main().
 *
 * Description:
 *	Sets the fields of the info_t struct based on the command-line args.
 *	Parses the argument string to create an argv & updates
 *	other relevant fields. Also, replaces aliases and variables in the args.
 *
 * Return: None.
 */
void set_inf(info_t *info, char **av)
{
	int index = 0;

	info->fname = av[0];
	if (info->arg)
	{
		info->argv = str_tow(info->arg, " \t");
		if (!info->argv)
		{

			info->argv = malloc(sizeof(char *) * 2);
			if (info->argv)
			{
				info->argv[0] = str_dupp(info->arg);
				info->argv[1] = NULL;
			}
		}
		for (index = 0; info->argv && info->argv[index]; index++)
			;
		info->argc = index;

		replace_alias(info);
		replace_vars(info);
	}
}

/**
 * free_inf - Frees memory associated with the info_t structure.
 * @info: Pointer to the info_t structure whose memory needs to be freed.
 * @all: Flag indicating whether to free all associated memory (1) or not (0).
 *
 * Description:
 *	Frees the memory allocated for the fields of the info_t structure.
 *	Depending on the 'all' flag, it may free additional resources like lists,
 *	command buffers, environment variables, and file descriptors.
 *
 * Return: None.
 */
void free_inf(info_t *info, int all)
{
	ffree(info->argv);
	info->argv = NULL;
	info->path = NULL;
	if (all)
	{
		if (!info->cmd_buff)
			free(info->arg);
		if (info->env)
			free_list(&(info->env));
		if (info->history)
			free_list(&(info->history));
		if (info->alias)
			free_list(&(info->alias));
		ffree(info->environ);
			info->environ = NULL;
		be_free((void **)info->cmd_buff);
		if (info->readfd > 2)
			close(info->readfd);
		_putchar(BUFF_FLUSH);
	}
}
