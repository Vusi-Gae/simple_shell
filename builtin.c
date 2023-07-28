#include "shell.h"

/**
 * _myexit - Exits the shell with a given exit status.
 * @info: Structure containing potential arguments. Used to maintain
 *         constant function prototype.
 *
 * Return: Exits with a given exit status (0) if info.argv[0] != "exit".
 */
int _myexit(info_t *info)
{
	int exit_check;

	if (info->argv[1]) /* If there is an exit argurment */
	{
		exit_check = _erratoi(info->argv[1]);
		if (exit_check == -1)
		{
			info->status = 2;
			print_error(info, "Illegal number: ");
			_eputs(info->argv[1]);
			_eputchar('\n');
			return (1);
		}
		info->err_num = _erratoi(info->argv[1]);
		return (-2);
	}
	info->err_num = -1;
	return (-2);
}

/**
 * _mycd - Changes the current directory of the process.
 * @info: Structure containing potential args. Used to maintain
 *        constant function prototype.
 *
 * Return: Always 0.
 */
int _mycd(info_t *info)
{
	char *z, *_dir, buffer[1024];
	int chdir_rett;

	z = getcwd(buffer, 1024);
	if (!z)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!info->argv[1])
	{
		_dir = _getenv(info, "HOME=");
		if (!_dir)
			chdir_rett = /* TODO: what could this be? */
				chdir((_dir = _getenv(info, "PWD=")) ? _dir : "/");
		else
			chdir_rett = chdir(_dir);
	}
	else if (_strcmp(info->argv[1], "-") == 0)
	{
		if (!_getenv(info, "OLDPWD="))
		{
			_puts(z);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(info, "OLDPWD=")), _putchar('\n');
		chdir_rett = /* TODO: what could this be? */
			chdir((_dir = _getenv(info, "OLDPWD=")) ? _dir : "/");
	}
	else
		chdir_rett = chdir(info->argv[1]);
	if (chdir_rett == -1)
	{
		print_error(info, "can't cd to ");
		_eputs(info->argv[1]), _eputchar('\n');
	}
	else
	{
		_setenv(info, "OLDPWD", _getenv(info, "PWD="));
		_setenv(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * _myhelp - Displays help message.
 * @info: Structure containing potential arguments. Used to maintain
 *         constant function prototype.
 *
 * Return: Always 0.
 */
int _myhelp(info_t *info)
{
	char **args_array;

	args_array = info->argv;
	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*args_array);
	return (0);
}
