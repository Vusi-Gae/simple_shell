#include "shell.h"

/**
 * get_history_file - Gets the path to the history file.
 * @info: Pointer to the parameter struct.
 *
 * Return: Allocated string containing the history file path or NULL on failure.
 */
char *get_history_file(info_t *info)
{
	char *buff, *_dir;

	_dir = _getenv(info, "HOME=");
	if (!_dir)
		return (NULL);
	buff = malloc(sizeof(char) * (_strlen(_dir) + _strlen(HIST_FILE) + 2));
	if (!buff)
		return (NULL);
	buff[0] = 0;
	_strcpy(buff, _dir);
	_strcat(buff, "/");
	_strcat(buff, HIST_FILE);
	return (buff);
}

/**
 * write_history - Writes the history entries to a file.
 * @info: Pointer to the parameter struct.
 *
 * Return: 1 on success, -1 on failure.
 */
int write_history(info_t *info)
{
	ssize_t fdd;
	char *_filename = get_history_file(info);
	list_t *_node = NULL;

	if (!_filename)
		return (-1);

	fdd = open(_filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(_filename);
	if (fdd == -1)
		return (-1);
	for (_node = info->history; _node; _node = _node->next)
	{
		_putsfd(_node->str, fdd);
		_putfd('\n', fdd);
	}
	_putfd(BUF_FLUSH, fdd);
	close(fdd);
	return (1);
}

/**
 * read_history - Reads the hist entries from a file.
 * @info: Ptr to the param struct.
 *
 * Return: The no of hist entries read on success, 0 otherwise.
 */
int read_history(info_t *info)
{
	int j, _last = 0, line_count = 0;
	ssize_t fdd, rd_len, ffsize = 0;
	struct stat st;
	char *buff = NULL, *file_name = get_history_file(info);

	if (!file_name)
		return (0);

	fdd = open(file_name, O_RDONLY);
	free(file_name);
	if (fdd == -1)
		return (0);
	if (!fstat(fdd, &st))
		ffsize = st.st_size;
	if (ffsize < 2)
		return (0);
	buff = malloc(sizeof(char) * (ffsize + 1));
	if (!buff)
		return (0);
	rd_len = read(fdd, buff, ffsize);
	buff[ffsize] = 0;
	if (rd_len <= 0)
		return (free(buff), 0);
	close(fdd);
	for (j = 0; j < ffsize; j++)
		if (buff[j] == '\n')
		{
			buff[j] = 0;
			build_history_list(info, buff + _last, line_count++);
			_last = j + 1;
		}
	if (_last != j)
		build_history_list(info, buff + _last, line_count++);
	free(buff);
	info->histcount = line_count;
	while (info->histcount-- >= HIST_MAX)
		delete_node_at_index(&(info->history), 0);
	renumber_history(info);
	return (info->histcount);
}

/**
 * build_history_list - Adds an entry to the history linked list
 * @info: Pointer to the parameter struct.
 * @buf: Buffer containing the command.
 * @linecount: The history linecount (histcount).
 *
 * Return: Always 0.
 */
int build_history_list(info_t *info, char *buf, int linecount)
{
	list_t *_node = NULL;

	if (info->history)
		_node = info->history;
	add_node_end(&_node, buf, linecount);

	if (!info->history)
		info->history = _node;
	return (0);
}

/**
 * renumber_history - Renumbers the history linked list after changes.
 * @info: Pointer to the parameter struct.
 *
 * Return: The new histcount.
 */
int renumber_history(info_t *info)
{
	list_t *_node = info->history;
	int j = 0;

	while (_node)
	{
		_node->num = j++;
		_node = _node->next;
	}
	return (info->histcount = j);
}
