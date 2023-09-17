#include "shell.h"

/**
 * main - Entry point for
 * the Simple Shell (Hsh)
 * @argc: Number of command-line arguments
 * @argv: Array of command-line argument strings
 * Return: Exit status code
 */

int main(int argc, char **argv)
{
	char *usr_in, **cmnd;
	int cnt = 0, status = 1, status_code = 0;

	(void) argc;

	if (argv[1] != NULL)
		file_scan(argv[1], argv);
	signal(SIGINT, handle_signal);
	while (status)
	{
		cnt++;
		if (isatty(STDIN_FILENO))
			prompt_line();
		usr_in = c_getline();
		if (usr_in[0] == '\0')
		{
			continue;
		}
		history(usr_in);
		cmnd = parse_comand(usr_in);
		if (str_cmp(cmnd[0], "exit") == 0)
		{
			c_exit(cmnd, usr_in, argv, cnt);
		}
		else if (bultn_check(cmnd) == 0)
		{
			status_code = ex_bltn(cmnd, status_code);
			all_free(cmnd, usr_in);
			continue;
		}
		else
		{
			status_code = verif_cmnd(cmnd, usr_in, cnt, argv);
		}
		all_free(cmnd, usr_in);
	}
	return (status_code);
}
