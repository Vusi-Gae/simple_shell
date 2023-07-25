#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

/* Buffer sizes for read and write operations */
#define BUFFER_SIZE_READ	2024
#define BUFFER_SIZE_WRITE	2024
#define BUF_FLUSH_IMMEDIATELY	-1

/* Command chaining types */
#define CHAIN_NORMAL	0
#define CHAIN_OR	1
#define CHAIN_AND	2
#define CHAIN_CUSTOM	3

/* Conversion options for convert_number() */
#define CONV_TO_LOWERCASE	1
#define CONV_TO_UNSIGNED	2

/* 1 if using system getline() */
#define USE_GETLINE	0
#define USE_STRTOK	0

#define HIST_FILE	".simple_shell_history.txt"
#define HIST_MAX	8192

extern char **environ;


/**
 * struct liststr - singly linked list
 * @num: the number field
 * @str: a string
 * @next: points to the next node
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

/**
 * struct passinfo - contains pseudo-arguements to pass into a function,
 * allowing uniform prototype for function pointer struct
 * @arg: A string generated from getline() containing arguments.
 * @argv:an array of strings generated from arg
 * @path: A string representing the path for the current command.
 * @argc: An integer representing the argument count.
 * @line_count: An unsigned integer representing the error count.
 * @err_num: An integer representing the error code for exit() calls.
 * @linecount_flag: A flag indicating whether to count this line of input.
 * @fname: A string representing the program filename.
 * @env: linked_list local copy of environ
 * @environ: Custom modified copy of environ from LL env
 * @history: the history node
 * @alias: the alias node command
 * @env_changed: on if environ was changed
 * @status: the return status of the last exec'd command
 * @cmd_buf: address of pointer to cmd_buf, on if chaining
 * @cmd_buf_type: CMD_type ||, &&, ;
 * @readfd: the fd from which to read line input
 * @histcount: the history line number count
 */
typedef struct passinfo
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int env_changed;
	int status;

	char **cmd_buf; /* pointer to cmd ; chain buffer, for memory mangement */
	int cmd_buf_type; /* CMD_type ||, &&, ; */
	int readfd;
	int histcount;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
		0, 0, 0}

/**
 * struct builtin - contains a builtin string and related function
 * @type: the builtin command flag
 * @func: the function
 */
typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;

/* str_to_int.c */
int check_interactive_mode(ShellInfo_t *infor);
int is_character_delimiter(char c, char *delimiter_string);
int is_alphabetic(int c);
int string_to_integer(char *str);

#endif
