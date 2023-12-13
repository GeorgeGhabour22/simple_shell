#ifndef _SIMPLE_H_
#define _SIMPLE_H_

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

#define CONVERT_LC	1
#define CONVERT_UNSIGN	2

#define RD_BUFF_SIZE 1024
#define WR_BUFF_SIZE 1024
#define BUFF_FLUSH -1

#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

#define HIST_FILE	".SimpleShell_Hist"
#define HIST_MAX	4096

extern char **environ;

/**
 * struct liststr - singly linked list
 * @num: the number field
 * @str: a string
 * @next: points to the next node
 */
typedef struct liststr
{
	char *str;
	int num;
	struct liststr *next;
} list_t;

/**
 * struct passinfo - Structure to hold information for the shell program.
 * @arg: Current command line argument.
 * @argv: Array of command line arguments.
 * @path: Path associated with the command.
 * @argc: Number of command line arguments.
 * @line_count: Count of lines processed.
 * @err_num: Error number if an error occurs.
 * @linecount_flag: Flag to indicate if line count needs to be incremented.
 * @fname: File name associated with the command.
 * @env: Linked list for environment variables.
 * @history: Linked list to store command history.
 * @alias: Linked list to store command aliases.
 * @environ: Array of environment variables.
 * @env_changed: Flag to indicate if the environment has been modified.
 * @status: Exit status of the last executed command.
 * @cmd_buff: Pointer to command buffer; chain buffer for memory management.
 * @cmd_buf_type: Type of command buffer (CMD_type ||, &&, ;).
 * @readfd: File descriptor for reading input.
 * @histcount: History count.
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
	char **cmd_buff;
	int cmd_buf_type;
	int readfd;
	int histcount;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;

/* 0x01.c functions*/
int is_interactive(info_t *);
int is_delimeter(char, char *);
int is_alpha(int);
int _atoi(char *);

/* 0x02.c functions */
int is_exit(info_t *);
int _command(info_t *);
int _help(info_t *);

/* 0x03.c functions */
int z_history(info_t *);
int z_alias(info_t *);

/* 0x04.c functions */
char *get_env(info_t *, const char *);
int z_env(info_t *);
int set_env(info_t *);
int unset_env(info_t *);
int inhabit_env_list(info_t *);

/* 0x05.c functions*/
void _eputs(char *);
int _eputch(char);
int _putfds(char c, int fd);
int _putsfds(char *str, int fd);

/* 0x06.c functions */
int error_atoi(char *);
void error_print(info_t *, char *);
int decimal_print(int, int);
char *cnv_n(long int, int, int);
void rm_comm(char *);

/* 0x07.c functions */
char *strn_copy(char *, char *, int);
char *strn_cat(char *, char *, int);
char *strn_char(char *, char);

/*0x08.c functions */
ssize_t gett_input(info_t *);
int gett_line(info_t *, char **, size_t *);
void signin_Handler(int);

/* 0x09.c functions */
char **gett_environ(info_t *);
int un_setenv(info_t *, char *);
int sett_env(info_t *, char *, char *);

/* 0x10.c functions */
void clear_inf(info_t *);
void set_inf(info_t *, char **);
void free_inf(info_t *, int);

/* 0x11.c functions */
char *get_history_file(info_t *info);
int write_history(info_t *info);
int read_history(info_t *info);
int build_history_list(info_t *info, char *buf, int linecount);
int renumber_history(info_t *info);

/* 0x12.c functions */
list_t *add_node(list_t **, const char *, int);
list_t *add_node_end(list_t **, const char *, int);
size_t print_list_str(const list_t *);
int delete_node_at_index(list_t **, unsigned int);
void free_list(list_t **);

/* 0x13.c functions */
size_t list_len(const list_t *);
char **list_to_strings(list_t *);
size_t print_list(const list_t *);
list_t *node_starts_with(list_t *, char *, char);
ssize_t get_node_index(list_t *, list_t *);

/* 0x14.c functions */
int be_free(void **);

/* 0x15.c functions */
int _iscmd(info_t *, char *);
char *dup_char(char *, int, int);
char *find_path(info_t *, char *, char *);

/* 0x16.c functions */
char *_memset(char *, char, unsigned int);
void ffree(char **);
void *_realloc(void *, unsigned int, unsigned int);

/* 0x17.c functions */
int hash(info_t *, char **);
int find_built_in(info_t *);
void find_command(info_t *);
void fork_command(info_t *);

/* 0x18.c functions */
int str_len(char *);
int str_cmp(char *, char *);
char *starts_with(const char *, const char *);
char *str_cat(char *, char *);
char **str_tow(char *, char *);

/* 0x19.c functions */
char *str_copy(char *, char *);
char *str_dupp(const char *);
void _puts(char *);
int _putchar(char);

/* 0x20.c functions */
int is_chain(info_t *, char *, size_t *);
void check_chain(info_t *, char *, size_t *, size_t, size_t);
int replace_alias(info_t *);
int replace_vars(info_t *);
int replace_string(char **, char *);

#endif
