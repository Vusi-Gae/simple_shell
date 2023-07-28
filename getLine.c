#include "shell.h"

/**
 * input_buf - Buffers chained commands.
 * @info: Parameter structure.
 * @buf: Address of buffer.
 * @len: Address of len var.
 *
 * Return: Bytes read.
 */
ssize_t input_buf(info_t *info, char **buf, size_t *len)
{
	ssize_t f = 0;
	size_t _len_p = 0;

	if (!*len)
	{
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		f = getline(buf, &_len_p, stdin);
#else
		f = _getline(info, buf, &_len_p);
#endif
		if (f > 0)
		{
			if ((*buf)[f - 1] == '\n')
			{
				(*buf)[f - 1] = '\0';
				f--;
			}
			info->linecount_flag = 1;
			remove_comments(*buf);
			build_history_list(info, *buf, info->histcount++);
			{
				*len = f;
				info->cmd_buf = buf;
			}
		}
	}
	return (f);
}

/**
 * get_input - Gets a line minus the newline
 * @info: Parameter structure
 *
 * Return: Bytes read
 */
ssize_t get_input(info_t *info)
{
	static char *_buf;
	static size_t b, t, _len;
	ssize_t a = 0;
	char **buff_p = &(info->arg), *ptr;

	_putchar(BUF_FLUSH);
	a = input_buf(info, &_buf, &_len);
	if (a == -1)
		return (-1);
	if (_len)
	{
		t = b;
		ptr = _buf + b;

		check_chain(info, _buf, &t, b, _len);
		while (t < _len)
		{
			if (is_chain(info, _buf, &t))
				break;
			t++;
		}

		b = t + 1;
		if (b >= _len)
		{
			b = _len = 0;
			info->cmd_buf_type = CMD_NORM;
		}

		*buff_p = ptr;
		return (_strlen(ptr));
	}

	*buff_p = _buf;
	return (a);
}

/**
 * read_buf - Reads a buffer.
 * @info: Parameter struct.
 * @buf: Buffer.
 * @i: Size.
 *
 * Return: k
 */
ssize_t read_buf(info_t *info, char *buf, size_t *i)
{
	ssize_t k = 0;

	if (*i)
		return (0);
	k = read(info->readfd, buf, READ_BUF_SIZE);
	if (k >= 0)
		*i = k;
	return (k);
}

/**
 * _getline - Gets the next line of input from STDIN.
 * @info: Parameter struct.
 * @ptr: Address of pointer to buffer, Pre-allocated or NULL.
 * @length: Size of preallocated ptr buffer if not NULL.
 *
 * Return: e
 */
int _getline(info_t *info, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t a, _len;
	size_t k;
	ssize_t h = 0, e = 0;
	char *y = NULL, *_new_p = NULL, *u;

	y = *ptr;
	if (y && length)
		e = *length;
	if (a == _len)
		a = _len = 0;

	h = read_buf(info, buf, &_len);
	if (h == -1 || (h == 0 && _len == 0))
		return (-1);

	u = _strchr(buf + a, '\n');
	k = u ? 1 + (unsigned int)(u - buf) : _len;
	_new_p = _realloc(y, e, e ? e + k : k + 1);
	if (!_new_p) /* MALLOC FAILURE! */
		return (y ? free(y), -1 : -1);

	if (e)
		_strncat(_new_p, buf + a, k - a);
	else
		_strncpy(_new_p, buf + a, k - a + 1);

	e += k - a;
	a = k;
	y = _new_p;

	if (length)
		*length = e;
	*ptr = y;
	return (e);
}

/**
 * sigintHandler - Blocks control-c.
 * @sig_num: the signal number
 *
 * Return: void
 */
void sigintHandler(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}
