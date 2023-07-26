#include "shell.h"

/**
 * my_exit_shell - Exits the shell.
 * @infor: Structure containing potential arguments. Used to maintain
 *         constant function prototype.
 *
 * Return: Exits with a given exit status (0) if infor->argv[0] != "exit".
 */
int my_exit_shell(infor_t *infor)
{
	int exit_check;

	if (infor->argv[1])
	{
		exit_check = _erratoi(infor->argv[1]);
		if (exit_check == -1)
		{
			infor->status = 2;
			print_error(infor, "Illegal number: ");
			_eputs(infor->argv[1]);
			_eputchar('\n');
			return (1);
		}
		infor->err_num = _erratoi(infor->argv[1]);
		return (-2);
	}
	infor->err_num = -1;
	return (-2);
}

/**
 * change_current_directory - Changes the current directory of the process.
 * @infor: Structure containing potential arguments. Used to maintain
 *         constant function prototype.
 *
 * Return: Always 0.
 */
int change_current_directory(infor_t *infor)
{
    char *current_dir, *target_dir, buffer[1024];
    int chdir_ret;

    current_dir = getcwd(buffer, 1024);
    if (!current_dir)
        _puts("TODO: >>getcwd failure emsg here<<\n");

    if (!infor->argv[1])
        change_to_home_directory(infor, &target_dir, &chdir_ret);
    else if (_strcmp(infor->argv[1], "-") == 0)
        change_to_previous_directory(infor, &current_dir, &chdir_ret);
    else
        chdir_ret = chdir(infor->argv[1]);

    handle_directory_change_results(infor, current_dir, target_dir, chdir_ret, buffer);
    return 0;
}

/**
 * show_help_message - Displays a help message for the shell.
 * @infor: Structure containing potential arguments. Used to maintain
 *         constant function prototype.
 *
 * Return: Always 0.
 */
int show_help_message(infor_t *infor)
{
	char **arg_array;

	arg_array = infor->argv;
	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*arg_array); /* temp att_unused workaround */
	return (0);
}

