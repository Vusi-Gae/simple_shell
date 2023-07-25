#include "shell.h"

/**
 * my_exit_shell - Exits the shell.
 * @infor: Pointer to the shell information struct.
 * Return: Exits with a given exit status (0) if infor->argv[0] != "exit".
 */
int my_exit_shell(infor_t *infor)
{
	int exit_check;

	if (infor->argv[1]) /* If there is an exit argument */
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
 * @infor: Pointer to the shell information struct.
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
    {
        target_dir = _getenv(infor, "HOME=");
        if (!target_dir)
            chdir_ret = chdir((target_dir = _getenv(infor, "PWD=")) ? target_dir : "/");
        else
            chdir_ret = chdir(target_dir);
    }
    else if (_strcmp(infor->argv[1], "-") == 0)
    {
        if (!_getenv(infor, "OLDPWD="))
        {
            _puts(current_dir);
            _putchar('\n');
            return (1);
        }
        _puts(_getenv(infor, "OLDPWD="));
        _putchar('\n');
        chdir_ret = chdir((target_dir = _getenv(infor, "OLDPWD=")) ? target_dir : "/");
    }
    else
        chdir_ret = chdir(infor->argv[1]);

    if (chdir_ret == -1)
    {
        print_error(infor, "can't cd to ");
        _eputs(infor->argv[1]), _eputchar('\n');
    }
    else
    {
        _setenv(infor, "OLDPWD", _getenv(infor, "PWD="));
        _setenv(infor, "PWD", getcwd(buffer, 1024));
    }
    return (0);
}

/**
 * show_help_message - Displays a help message for the shell.
 * @infor: Pointer to the shell information struct.
 * Return: Always 0.
 */
int show_help_message(infor_t *infor)
{
	char **arg_array;

	arg_array = infor->argv;
	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*arg_array);
	return (0);
}

