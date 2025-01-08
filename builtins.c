#include"shell.h"

/**
 * env_builtin - Prints all the environment variables.
 * This function iterates through the environment variable array
 * (environ) and prints each variable to the standard output, one per
 * line.
 */

void env_builtin(void)
{
	char **env = environ;

	while (*env != NULL)

	{
		printf("%s\n", *env);
		env++;
	}
}

/**
 * handle_builtin - Handles built-in commands.
 * This function checks the first argument of the command (cmd_args[0]).
 * If the command is "env", it calls env_builtin to print environment
 * variables. If the command is "exit", it terminates the program.
 * @cmd_args: The array of command arguments.
 * Return: 1 if a built-in command is executed, 0 otherwise.
 */

int handle_builtin(char **cmd_args)
{
	if (cmd_args == NULL || cmd_args[0] == NULL)
	return (0);

	if (strcmp(cmd_args[0], "env") == 0)
	{
		env_builtin();
		return (1);
	}

	if (strcmp(cmd_args[0], "exit") == 0)
	{
	cmd_exit();
	return (1);
	}

	return (0);
}
