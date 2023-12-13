#include "simple.h"

/**
 * _iscmd - Determine if the file is an executable command.
 * @info: The info struct.
 * @path: Path to the file.
 *
 * Return: 1 if true, 0 otherwise.
 */
int _iscmd(info_t *info, char *path)
{
	struct stat file_stat;

	(void)info;
	if (!path || stat(path, &file_stat))
	{
		return (0);
	}
	if (file_stat.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * dup_char - Duplicate chars.
 * @pathstr: The Path string.
 * @start: starting index.
 * @stop: stopping index.
 *
 * Return: pointer to the new buffer.
 */
char *dup_char(char *pathstr, int start, int stop)
{
	static char buff[1024];
	int index = 0, y = 0;

	for (y = 0, index = start; index < stop; index++)
		if (pathstr[index] != ':')
			buff[y++] = pathstr[index];
	buff[y] = 0;
	return (buff);
}

/**
 * find_path - finds this cmd in the Path string.
 * @info: the info struct.
 * @pathstr: the PATH string.
 * @cmd: the cmd to find.
 *
 * Return: full path of cmd if found or NULL.
 */
char *find_path(info_t *info, char *pathstr, char *cmd)
{
	int index = 0, curr_position = 0;
	char *p;

	if (!pathstr)
		return (NULL);
	if ((str_len(cmd) > 2) && starts_with(cmd, "./"))
	{
		if (_iscmd(info, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pathstr[index] || pathstr[index] == ':')
		{
			p = dup_char(pathstr, curr_position, index);
			if (!*p)
				str_cat(p, cmd);
			else
			{
				str_cat(p, "/");
				str_cat(p, cmd);
			}
			if (_iscmd(info, p))
				return (p);
			if (!pathstr[index])
				break;
			curr_position = index;
		}
		index++;
	}
	return (NULL);
}
