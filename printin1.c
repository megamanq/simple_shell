#include "shell.h"

/**
 * print_uns_num - Recursively print
 * an unsigned integer using _putchar
 * @num: The unsigned integer to be printed
 *
 * Description: This function prints an unsigned
 * integer character by character
 * using the _putchar function.
 *
 * Return: void
 */
void print_uns_num(unsigned int num)
{
	unsigned int abs_num = num;

	if ((abs_num / 10) > 0)
		print_uns_num(abs_num / 10);
	_putchar(abs_num % 10 + '0');
}

/**
 * print_err - Display an error message based on the command and loop count
 * @cmd: Command that caused the error
 * @er_cnt: Number of times the shell has looped
 * @prog_name: Name of the program
 * Return: void
 */
void print_err(char *cmd, int er_cnt, char **prog_name)
{
	char *error_msg;

	LOG(prog_name[0]);
	LOG(": ");
	error_msg = c_itoa(er_cnt);
	LOG(error_msg);
	free(error_msg);
	LOG(": ");
	LOG(cmd);
	LOG(": No such file or directory\n");
}

/**
 * echo_builtin - Handle various Echo cases.
 * @cmd_args: Parsed Command and Arguments.
 * @last_cmd_statu: Status of the Last Executed Command.
 * Return: Always 0, or execute normal Echo.
 */

int echo_builtin(char **cmd_args, int last_cmd_statu)
{
	char *path;
	unsigned int parent_pid = getppid();

	if (c_strncmp(cmd_args[1], "$?", 2) == 0)
	{
		print_integer(last_cmd_statu);
		LOG("\n");
	}
	else if (c_strncmp(cmd_args[1], "$$", 2) == 0)
	{
		print_uns_num(parent_pid);
		LOG("\n");
	}
	else if (c_strncmp(cmd_args[1], "$PATH", 5) == 0)
	{
		path = c_getenv("PATH");
		LOG(path);
		LOG("\n");
		free(path);
	}
	else
	{
		return (execute_echo(cmd_args));
	}
	return (1);
}

/**
 * p_error - Print Custom Error Message
 * @program_name: Name of the shell program
 * @error_count: Error count
 * @command: Command that caused the error
 * Return: Void
 */
void p_error(char **program_name, int error_count, char **command)
{
	char *error_count_str = c_itoa(error_count);

	LOG(program_name[0]);
	LOG(": ");
	LOG(error_count_str);
	LOG(": ");
	LOG(command[0]);
	LOG(": Illegal number: ");
	LOG(command[1]);
	LOG("\n");
	free(error_count_str);
}

/**
 * env_disp - Display Environment Variables.
 * @cmd_args: Parsed Command (unused).
 * @status: Status of the Last Command Executed (unused).
 * Return: Always 0.
 */

int env_disp(char **cmd_args, int status)
{
	size_t index = 0;
	int length;

	(void)cmd_args;
	(void)status;

	while (environ[index] != NULL)
	{
		length = str_lenght(environ[index]);
		write(1, environ[index], length);
		write(STDOUT_FILENO, "\n", 1);
		index++;
	}
	return (0);
}
