#include "simple.h"

/**
 * is_exit - exits the shell.
 * @info: Struct that holds potential args.
 *         Used to maintain the  const. fnc prototype.
 *  Return: exits with a given exit status.
 *         (0) if != "exit"
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
 * _command - changes current directory of the process.
 * @info: Structure containing potential args. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
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
 * _help - changes current directory of the process.
 * @info: Structure containing potential args. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
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
