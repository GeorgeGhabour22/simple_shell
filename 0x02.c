#include "simple.h"

/**
 * is_exit - Checks if the command is an "exit" command.
 * @info: Pointer to the info_t structure containing shell information.
 *
 * Return:
 *   -1 if the command is not an "exit" command.
 *   1 if an error occurs (illegal number).
 *   -2 if the command is a valid "exit" command.
 */
int is_exit(info_t *info)
{
	int exitcheck;

	if (info->argv[1])
	{
		exitcheck = error_atoi(info->argv[1]);
		if (exitcheck == -1)
		{
			info->status = 2;
			error_print(info, "Illegal number: ");
			_eputs(info->argv[1]);
			_eputch('\n');
			return (1);
		}
		info->err_num = error_atoi(info->argv[1]);
		return (-2);
	}
	info->err_num = -1;
	return (-2);
}

/**
 * _command - Handles the execution of the "cd" command.
 * @info: Pointer to the info_t structure containing shell information.
 *
 * Return: 0 on success, 1 on failure.
 */
int _command(info_t *info)
{
	char *s, *dir, buffer[1024];
	int chdir_ret;

	s = getcwd(buffer, 1024);
	if (!s)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!info->argv[1])
	{
		dir = get_env(info, "HOME=");
		if (!dir)
			chdir_ret =
				chdir((dir = get_env(info, "PWD=")) ? dir : "/");
		else
			chdir_ret = chdir(dir);
	}
	else if (str_cmp(info->argv[1], "-") == 0)
	{
		if (!get_env(info, "OLDPWD="))
		{
			_puts(s);
			_putchar('\n');
			return (1);
		}
		_puts(get_env(info, "OLDPWD=")), _putchar('\n');
		chdir_ret =
			chdir((dir = get_env(info, "OLDPWD=")) ? dir : "/");
	}
	else
		chdir_ret = chdir(info->argv[1]);
	if (chdir_ret == -1)
	{
		error_print(info, "can't cd to ");
		_eputs(info->argv[1]), _eputch('\n');
	}
	else
	{
		sett_env(info, "OLDPWD", get_env(info, "PWD="));
		sett_env(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * _help - Displays information about built-in commands.
 * @info: Pointer to the info_t structure containing shell information.
 *
 * Return: Always returns 0.
 */
int _help(info_t *info)
{
	char **arg_array;

	arg_array = info->argv;
	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*arg_array); /* temp att_unused workaround */
	return (0);
}
