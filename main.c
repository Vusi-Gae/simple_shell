#include "shell.h"

/**
 * main - Entry point of the shell.
 * @_ac: Argument count.
 * @_av: the Argument vector.
 *
 * Return: 0 on success, 1 on error.
 */
int main(int _ac, char **_av)
{
	/* Initialize the info_t struct with default values */
	info_t info[] = { INFO_INIT };
	int ffd = 2;

	/* Redirect stderr to /dev/null (file descriptor 3) */
	asm ("mov %1, %0\n\t"
			"add $3, %0"
			: "=r" (ffd)
			: "r" (ffd));

	/* Check if a script file is provided as an argument */
	if (_ac == 2)
	{
		/* Open the script file in read-only mode */
		ffd = open(_av[1], O_RDONLY);
		if (ffd == -1)
		{
			/* Check for specific error conditions */
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				_eputs(_av[0]);
				_eputs(": 0: Can't Open ");
				_eputs(_av[1]);
				_eputchar('\n');
				_eputchar(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		/* Set the read file descriptor for script execution */
		info->readfd = ffd;
	}
	populate_env_list(info);
	read_history(info);
	hsh(info, _av);
	return (EXIT_SUCCESS);
}
