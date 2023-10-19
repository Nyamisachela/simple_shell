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

/* for read/write buffers */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/* for command chaining */
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

/* for convert_number() */
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

/* 1 if using system getline() */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

extern char **environ;


/**
 * struct to_liststr - singly linked list
 * @number: the number field
 * @str: a string
 * @to_next: points to the next node
 */

typedef struct liststr
{
	int number;
	char *strr;
	struct liststr *to_next;
} list_t;

/**
 * struct passinfo - contains pseudo-arguements to pass into a function,
 * allowing uniform prototype for function pointer struct
 * @arg: a string generated from getline containing arguements
 * @argv:an array of strings generated from arg
 * @path: a string path for the current command
 * @argc: the argument count
 * @line_count: used to error count
 * @err_number: the error code for exit()s
 * @to_linecount_flags: this line of input if on count
 * @file_name: the program filename
 * @envv: linked list local copy of environ
 * @environs: custom modified copy of environ from LL env
 * @_history: the history node
 * @alias: the alias node
 * @envv_changer: on if environ was changed
 * @status: the return status of the last exec'd command
 * @cmd_buffer: address of pointer to cmd_buf, on if chaining
 * @cmd_buffer_type: CMD_type ||, &&, ;
 * @to_readfd: the fd from which to read line input
 * @to_histcount: the history line number count
 */
typedef struct passinfo
{
	char *arg;
	char **argv;
	char *paths;
	int argc;
	unsigned int line_count;
	int err_number;
	int to_linecount_flags;
	char *file_name;
	list_t *envv;
	list_t *_history;
	list_t *alias;
	char **environs;
	int envv_changer;
	int status;

	char **cmd_buffer; /* pointer to cmd ; chain buffer, for memory mangement */
	int cmd_buffer_type; /* CMD_type ||, &&, ; */
	int to_readfd;
	int to_histcount;
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


/* toem_shloop.c */
int to_hsh(info_t *, char **);
int to_find_builtin(info_t *);
void to_find_cmd(info_t *);
void to_fork_cmd(info_t *);

/* toem_parser.c */
int to_is_cmd(info_t *, char *);
char *to_dup_char(char *, int, int);
char *to_find_path(info_t *, char *, char *);

/* loophsh.c */
int loophsh(char **);

/* toem_errors.c */
void to_eputs(char *);
int to_eputchar(char);
int to_putfd(char c, int fd);
int to_putsfd(char *str, int fd);

/* toem_string.c */
int to_strlen(char *);
int to_strcmp(char *, char *);
char *to_start_with(const char *, const char *);
char *to_strcat(char *, char *);

/* toem_string1.c */
char *to_strcpy(char *, char *);
char *to_strdup(const char *);
void to_puts(char *);
int to_putchar(char);

/* toem_exits.c */
char *to_strncpy(char *, char *, int);
char *to_strncat(char *, char *, int);
char *to_strchr(char *, char);

/* toem_tokenizer.c */
char **to_strtow(char *, char *);
char **to_strtow2(char *, char );

/* toem_realloc.c */
char *to_memset(char *, char, unsigned int);
void to_ffree(char **);
void *to_reallocate(void *, unsigned int, unsigned int);

/* toem_memory.c */
int to_bfree(void **);

/* toem_atoi.c */
int to_interactive(info_t *);
int to_delim(char, char *);
int to_alpha(int);
int to_atoi(char *);

/* toem_errors1.c */
int to_erratoi(char *);
void to_print_error(info_t *, char *);
int to_print_d(int, int);
char *to_convert_number(long int, int, int);
void to_remove_comment(char *);

/* toem_builtin.c */
int to_myexit(info_t *);
int to_mycd(info_t *);
int to_myhelp(info_t *);

/* toem_builtin1.c */
int to_myhistory(info_t *);
int to_myalias(info_t *);

/*toem_getline.c */
ssize_t to_get_input(info_t *);
int to_getline(info_t *, char **, size_t *);
void to_sigintHandle(int);

/* toem_getinfo.c */
void to_clear_info(info_t *);
void to_set_info(info_t *, char **);
void to_free_info(info_t *, int);

/* toem_environ.c */
char *to_getenv(info_t *, const char *);
int to_myenv(info_t *);
int to_mysetenv(info_t *);
int to_myunsetenv(info_t *);
int to_populate_env_list(info_t *);

/* toem_getenv.c */
char **to_get_environs(info_t *);
int to_unsetenv(info_t *, char *);
int to_setenv(info_t *, char *, char *);

/* toem_history.c */
char *to_get_history_file(info_t *_infor);
int to_write_history(info_t *_infor);
int to_read_history(info_t *_infor);
int to_build_history_list(info_t *_infor, char *buffer, int line_count);
int to_renumber_history(info_t *_infor);

/* toem_lists.c */
list_t *to_add_node(list_t **, const char *, int);
list_t *to_add_node_end(list_t **, const char *, int);
size_t to_print_list_str(const list_t *);
int to_delete_node_at_ind(list_t **, unsigned int);
void to_free_list(list_t **);

/* toem_lists1.c */
size_t to_list_length(const list_t *);
char **to_list_to_string(list_t *);
size_t to_print_list(const list_t *);
list_t *to_node_start_with(list_t *, char *, char);
ssize_t to_get_node_ind(list_t *, list_t *);

/* toem_vars.c */
int to_is_chain(info_t *, char *, size_t *);
void to_check_chain(info_t *, char *, size_t *, size_t, size_t);
int to_replace_alias(info_t *);
int to_replace_vars(info_t *);
int to_replace_string(char **, char *);

#endif
