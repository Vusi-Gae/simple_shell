#include "shell.h"

/**
 * hsh - Main shell loop for the custom shell.
 * @info: Pointer to the parameter and returns info structure.
 * @av: The argument vector from the main function.
 *
 * Return: Exit status code:
 * 		0 on successful execution,
 * 		1 on general error,
 * 		or an error code if a specific error occurred during execution.
 */
int hsh(infor_t *infor, char **av)
{
	ssize_t results = 0;
	int builtin_ret = 0;

	while (results != -1 && builtin_ret != -2)
	{
		clear_info(infor);
		if (interactive(infor))
			_puts("$ ");
		_eputchar(BUF_FLUSH);
		results = get_input(infor);
		if (results != -1)
		{
			set_info(infor, av);
			builtin_ret = find_builtin(infor);
			if (builtin_ret == -1)
				find_cmd(infor);
		}
		else if (interactive(infor))
			_putchar('\n');
		free_info(infor, 0);
	}
	write_history(infor);
	free_info(infor, 1);
	if (!interactive(infor) && infor->status)
		exit(infor->status);
	if (builtin_ret == -2)
	{
		if (infor->err_num == -1)
			exit(infor->status);
		exit(infor->err_num);
	}
	return (builtin_ret);
}

/**
 * find_builtin - Finds a builtin command and executes it.
 * @info: A pointer to the parameter and return info struct.
 *
 * Return: -1 if builtin not found,
 * 	0 if builtin executed successfully,
 * 	1 if builtin found but not successful,
 * 	2 if builtin signals exit()
 */
int find_builtin(infor_t *infor)
{
	int i, built_in_ret = -1;
	builtin_table builtintbl[] = {
		{"exit", _myexit},
		{"env", _myenv},
		{"help", _myhelp},
		{"history", _myhistory},
		{"setenv", _mysetenv},
		{"unsetenv", _myunsetenv},
		{"cd", _mycd},
		{"alias", _myalias},
		{NULL, NULL}
	};

	for (i = 0; builtintbl[i].type; i++)
		if (_strcmp(infor->argv[0], builtintbl[i].type) == 0)
		{
			infor->line_count++;
			built_in_ret = builtintbl[i].func(infor);
			break;
		}
	return (built_in_ret);
}

/**
 * find_cmd - Searches for a command in the dir listed in the PATH enviro var.
 * @info: A pointer to the parameter and return info structure.
 *
 * Return: This function returns void.
 */
void find_cmd(infor_t *infor)
{
	char *path = NULL;
	int i, k;

	infor->path = infor->argv[0];
	if (infor->linecount_flag == 1)
	{
		info->line_count++;
		info->linecount_flag = 0;
	}
	for (i = 0, k = 0; infor->arg[i]; i++)
		if (!is_delim(infor->arg[i], " \t\n"))
			k++;
	if (!k)
		return;

	path = find_path(infor, _getenv(infor, "PATH="), infor->argv[0]);
	if (path)
	{
		infor->path = path;
		fork_cmd(infor);
	}
	else
	{
		if ((interactive(infor) || _getenv(infor, "PATH=")
					|| infor->argv[0][0] == '/') && is_cmd(infor, infor->argv[0]))
			fork_cmd(infor);
		else if (*(infor->arg) != '\n')
		{
			infor->status = 127;
			print_error(infor, "not found\n");
		}
	}
}

/**
 * fork_cmd - Forks a new process and executes a command using exec.
 * @info: A pointer to the parameter and return info structure.
 *
 * Return: This function returns void.
 */
void fork_cmd(infor_t *infor)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		/* TODO: PUT ERROR FUNCTION */
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(infor->path, infor->argv, get_environ(infor)) == -1)
		{
			free_info(infor, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
		/* TODO: PUT ERROR FUNCTION */
	}
	else
	{
		wait(&(infor->status));
		if (WIFEXITED(infor->status))
		{
			infor->status = WEXITSTATUS(infor->status);
			if (infor->status == 126)
				print_error(infor, "Permission denied\n");
		}
	}
}
