#include "shell.h"

/**
 * is_cmd - Determines if a file is an executable command.
 * @infor: The info struct (unused in this function).
 * @_path: Path to the file.
 *
 * Return: 1 if 'path' points to a regular file 0 otherwise.
 */
int is_cmd(info_t *infor, char *_path)
{
	struct stat st;

	(void)infor; /* Unused parameter */
	if (!_path || stat(_path, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1); /* 'path' points to a regular file */
	}
	return (0); /* 'path' does not point to a regular file */
}

/**
 * dup_chars - Duplicates characters from 'pathstr' starting from 'start' to 'stop'.
 * @path_str: The PATH string.
 * @start: Starting index to copy from.
 * @stop: Stopping index to copy to.
 *
 * Return: Pointer to a new buffer containing the duplicated characters.
 */
char *dup_chars(char *path_str, int start, int stop)
{
	static char buff[1024];
	int j = 0, h = 0;

	for (h = 0, j = start; j < stop; j++)
		if (path_str[j] != ':')
			buff[h++] = path_str[j];
	buff[h] = 0;
	return (buff);
}

/**
 * find_path - Finds the full path of the 'cmd' in the 'PATH' string.
 * @infor: The info struct (unused in this function).
 * @path_str: The PATH string.
 * @cmd: The command to find.
 *
 * Return: Full path of 'cmd' if found, or NULL if not found.
 */
char *find_path(info_t *infor, char *path_str, char *cmd)
{
	int j = 0, curr_poss = 0;
	char *_path;

	if (!path_str)
		return (NULL);
	/* Check if 'cmd' is a relative path starting with "./" */
	if ((_strlen(cmd) > 2) && starts_with(cmd, "./"))
	{
		if (is_cmd(infor, cmd))
			return (cmd);
	}

	/* Loop through 'path_str' to find 'cmd' in the directories */
	while (1)
	{
		if (!path_str[j] || path_str[j] == ':')
		{
			/* Duplicate the path segment from 'path_str' */
			_path = dup_chars(path_str, curr_poss, j);
			if (!*_path)
				_strcat(_path, cmd);
			else
			{
				_strcat(_path, "/");
				_strcat(_path, cmd);
			}

			/* Check if the full path 'path' is an executable command */
			if (is_cmd(infor, _path))
				return (_path);

			/* Move to the next segment in 'pathstr' */
			if (!path_str[j])
				break;
			curr_poss = j;
		}
		j++;
	}
	return (NULL);
}
