#ifndef SHELL_H
#define SHELL_H

extern char **environ;

#define BUFFSIZ 1024
#define DELIMETRE " \t\r\n\a"
#define LOG(c) (write(STDOUT_FILENO, c, str_lenght(c)))

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <linux/limits.h>

/**
 * String Functions
*/

int int_length(int number);
char *str_cpy(char *destination, char *source);
char *c_strtok(char *str, const char *delim);
void c_puts(char *string);
int str_lenght(char *str);
int str_cmp(char *str1, char *str2);
char *str_findchar(char *str, char ch);
char *str_duplicate(char *src);
char *str_concat(char *destination, char *source);
char *c_strncpy(char *destination, char *source, int length);
unsigned int isDelimiter(char character, const char *string);
void handle_sharp(char *input);
int c_strncmp(const char *str1, const char *str2, size_t numb);


/**
 * Memory Mangment
*/

void all_free(char **commands, char *input_line);
void *c_calloc(unsigned int size);
void *c_realloc(void *old_ptr, unsigned int old_siz, unsigned int nw_siz);
char *c_memcopy(char *new_dest, char *new_src, unsigned int length);
void *arr_fill(void *dest, int byte, unsigned int length);
void envir_free(char **environment);

/**
 * printing
*/

void print_uns_num(unsigned int num);
void print_err(char *cmd, int er_cnt, char **prog_name);
int echo_builtin(char **cmd_args, int last_cmd_statu);
void p_error(char **program_name, int error_count, char **command);
int env_disp(char **cmd_args, int status);
void prompt_line(void);
int _putchar(char ch);
int execute_echo(char **cmd_args);
void print_integer(int num);

/**
 * scaning and files
*/

void shell_exit_file(char **args, char *line, FILE *file_desc);
void handle_file(char *line, int er_cnt, FILE *f_desc, char **prog_name);
char *c_getenv(char *var_name);
char *c_getline(void);
void file_scan(char *filename, char **argv);

/**
 * shell helpers
*/

void c_exit(char **args, char *user_input, char **program_name, int cmd_cnt);
int verif_cmnd(char **cmnd, char *usr_in, int err_c, char **prog_name);
int show_help(char **command, __attribute__((unused)) int status);
int ex_bltn(char **command, int error_status);
int history_display(char **cmd_args, int status);
int change_directory(char **cmd_args, __attribute__((unused)) int lst_cmd_sta);
int history(char *us_in);
char *build_path(char *token, char *directory);
int bultn_check(char **command);
void create_environment(char **env_copy);
char **parse_comand(char *line);
int excmd_path(char **command);
void handle_signal(int signal);

/**
 * Conversion
*/

int c_atoi(char *s);
char *c_itoa(unsigned int num);
int c_isalpha(char ch);
void rev_arr(char *inputArray, int arrayLength);

/**
 * struct buillttin - Structure to store a built-in
 * command and its associated function
 * @command: Pointer to a character representing
 * the built-in command
 * @funct: Pointer to the function to execute when
 * the built-in command is invoked
 */
typedef struct  buillttin
{
	char *command;
	int (*funct)(char **line, int er);
} built_list;

#endif  /* SHELL_H */
