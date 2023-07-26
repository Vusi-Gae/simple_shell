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

/* Macros for read/write buffers */
#define READ_BUF_SIZE	1024
#define WRITE_BUF_SIZE	1024
#define BUF_FLUSH	-1

/* Macros for command chaining */
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

/* Macros for convert_number() */
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

/* Set to 1 if using system getline() */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

extern char **environ;

/**
 * struct liststr - singly linked list for strings
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
 * struct passinfo - contains pseudo-arguments to pass into a function,
 * allowing uniform prototype for function pointer struct
 * @arg: a string generated from getline containing arguments
 * @argv: an array of strings generated from arg
 * @path: a string path for the current command
 * @argc: the argument count
 * @line_count: the error count
 * @err_num: the error code for exit()s
 * @linecount_flag: if on count this line of input
 * @fname: the program filename
 * @env: linked list local copy of environ
 * @environ: custom modified copy of environ from LL env
 * @history: the history node
 * @alias: the alias node
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

	char **cmd_buf; /* Pointer to cmd ; chain buffer, for memory management */
	int cmd_buf_type; /* CMD_type ||, &&, ; */
	int readfd;
	int histcount;
} infor_t;

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
	int (*func)(infor_t *);
} builtin_table;

/* Function prototypes */
/* str_to_int.c */
int check_interactive_mode(infor_t *infor);
int is_character_delimiter(char c, char *delimiter_string);
int is_alphabetic(int c);
int string_to_integer(char *str);

/* _builtin.c */
int my_exit_shell(infor_t *infor);
int change_current_directory(infor_t *infor);
int show_help_message(infor_t *infor);
int _erratoi(const char *str);
void print_error(infor_t *infor, const char *msg);
void _eputs(const char *);
int _eputchar(char c);
char *_getenv(infor_t *infor, const char *);
int _strcmp(const char *s1, const char *);
int _setenv(infor_t *infor, const char *name, const char *value);
void change_to_home_directory(infor_t *infor, char **target_dir, int *chdir_ret);
void change_to_previous_directory(infor_t *infor, char **current_dir, int *chdir_ret);
void handle_directory_change_results(infor_t *infor, char *current_dir, char *target_dir, int chdir_ret, char *buffer);

/* _builtin0.c */
int display_history(infor_t *infor);
int unset_alias(infor_t *infor, char *alias_str);
int set_alias(infor_t *infor, char *alias_str);
int print_alias(list_t *alias_node);
int manage_alias(infor_t *infor);
void print_list(list_t *head);
char *_strchr(const char *s, int c);
list_t *add_node_end(list_t **head, char *str, int len);
unsigned int get_node_index(list_t *head, list_t *node);
list_t *node_starts_with(list_t *head, const char *str, char c);
int delete_node_at_index(list_t **head, unsigned int index);
void _putchar(char c);
void _puts(const char *str);

/* environ.c */
void print_list(list_t *head);
char *starts_with(const char *str, const char *prefix);
int setenv_variable(infor_t *infor, const char *name, const char *value);
void unsetenv_variable(infor_t *infor, const char *name);
int print_current_environment(infor_t *infor);
void print_list_str(list_t *head);
char *get_environment_variable(infor_t *infor, const char *name);
int set_environment_variable(infor_t *infor);
int unset_environment_variable(infor_t *infor);
int populate_environment_list(infor_t *infor);

/* errors.c */
void _eputs(const char *str);
int _eputchar(char c);
int _putfd(char character_to_write, int fd);
int _putsfd(char *string_to_print, int fd);

/* errors1.c */
int _erratoi(const char *str);
void print_error(infor_t *infor, const char *error_type);
int print_d(int input, int fd);
char *convert_number(long int num, int base, int flags);
void remove_comments(char *buf);

#endif /* _SHELL_H_ */
