#include "simple.h"

/**
 * main - Entry point.
 * @ac: Args count.
 * @av: Args vector.
 *
 * Return: 0 on success, 1 on Fail.
 */
int main(int ac, char **av)
{
	info_t info[] = { INFO_INIT };
	int fds = 2;

	asm ("mov %1, %0\n\t"
		"add $3, %0"
		: "=r" (fds)
		: "r" (fds));

	if (ac == 2)
	{
		fds = open(av[1], O_RDONLY);
		if (fds == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				_eputs(av[0]);
				_eputs(": 0: Can't open ");
				_eputs(av[1]);
				_eputch('\n');
				_eputch(BUFF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		info->readfd = fds;
	}
	inhabit_env_list(info);
	read_history(info);
	hash(info, av);
	return (EXIT_SUCCESS);
}
