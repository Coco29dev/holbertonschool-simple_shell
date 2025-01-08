#include "shell.h"

/**
 * handle_builtin - Handles built-in commands.
 * @cmd_args: The array of arguments for the command.
 * Return: 1 if the command is built-in, 0 otherwise.
 */
int handle_builtin(char **cmd_args)
{
	if (cmd_args[0] != NULL && strcmp(cmd_args[0], "exit") == 0)
	{
		free(cmd_args);
		exit(0);
	}
	return (0);
}
