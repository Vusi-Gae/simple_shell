#ifndef SHELL_H
#define SHELL_H

#include <limits.h>

/* Struct to hold shell information */
typedef struct infor {
	char *file_name; /* Name of the shell program file */
	int line_count; /* Current line count in the shell */
	int argc; /* Number of arguments passed to the shell */
	char **argv; /* Array of arguments passed to the shell */
	int status; /* Status code for the shell */
	int readfd; /* File descriptor for reading input */
	list_t *env; /* Linked list to store environment variables */
} infor_t;

/* Singly linked list node */
typedef struct list {
	char *str;
	struct list *next;
} list_t;

/* Function prototypes */
int check_interactive_mode(infor_t *infor);
int is_character_delimiter(char c, char *delimiter_string);
int is_alphabetic(int c);
int string_to_integer(char *str);
int my_exit_shell(infor_t *infor);
int change_current_directory(infor_t *infor);
int show_help_message(infor_t *infor);
int print_current_environment(infor_t *infor);
char *get_environment_variable(infor_t *infor, const char *name);
int set_environment_variable(infor_t *infor);
int unset_environment_variable(infor_t *infor);
int populate_environment_list(infor_t *infor);
int _erratoi(char *str);
void print_error(infor_t *infor, char *error_type);
int print_d(int input, int fd);
char *convert_number(long int num, int base, int flags);
void remove_comments(char *buf);

#endif /* SHELL_H */

