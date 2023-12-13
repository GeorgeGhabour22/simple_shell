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

