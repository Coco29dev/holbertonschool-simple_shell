#include"shell.h"

void env_builtin(void)
{
	char **env = environ;
	while (*env != NULL)
	{
		printf("%s\n", *env);
		env++;
	}
}

int handle_builtin(char **cmd_args)
{
	if (cmd_args == NULL || cmd_args[0] == NULL)
	return 0;

	if (strcmp(cmd_args[0], "env") == 0)
	{
		env_builtin();
		return 1;
	}

	if (strcmp(cmd_args[0], "exit") == 0)
	{
	exit(0);
	}
	if (cmd_args[0] != NULL && strcmp(cmd_args[0], "exit") == 0)
	{
	free(cmd_args);
	exit(0);
	}

	return 0;
}
