#include "shell.h"

/**
 * prompt_line - Print Shell Promp Line
 */
void prompt_line(void)
{
	LOG("$ ");
}

/**
 * _putchar - Write a character to standrd output.
 * @ch: The character to print.
 * Return: 1 on success, -1 on error (errno is set).
 */

int _putchar(char ch)
{
	return (write(1, &ch, 1));
}

/**
 * execute_echo - Execute a Normal Echo Command
 * @cmd_args: Parsed Command
 * Return: 1 for Success, -1 for Failure
 */

int execute_echo(char **cmd_args)
{
	pid_t child_pid;
	int child_status;

	child_pid = fork();
	if (child_pid == 0)
	{
		if (execve("/bin/echo", cmd_args, environ) == -1)
		{
			return (-1);
		}
		exit(EXIT_FAILURE);
	}
	else if (child_pid < 0)
	{
		return (-1);
	}
	else
	{
		do {
			waitpid(child_pid, &child_status, WUNTRACED);
		} while (!WIFEXITED(child_status) && !WIFSIGNALED(child_status));
	}
	return (1);
}

/**
 * print_integer - Recursively print an integer using _putchar
 * @num: The integer to be printed
 *
 * Description: This function prints an integer character by character
 * using the _putchar function, including handling negative integers.
 *
 * Return: void
 */

void print_integer(int num)
{
	unsigned int abs_num = num;

	if (num < 0)
	{
		_putchar('-');
		abs_num = -abs_num;
	}
	if ((abs_num / 10) > 0)
		print_uns_num(abs_num / 10);
	_putchar(abs_num % 10 + '0');
}
