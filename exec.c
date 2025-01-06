#include "shell.h"

/**
 * execute_command - execute
 * @cmd: commande
 * Return: nothing
 */


void execute_command(char *cmd)
{
	pid_t pid = fork();

	if (pid == 0)
	{
	char *argv[2];
	char *envp[1];

	argv[0] = cmd;
	argv[1] = NULL;
	envp[0] = NULL;

	if (execve(cmd, argv, envp) == -1)
	{
		perror(cmd);
	}
	exit(1);
	}
	else if (pid < 0)
	{
	perror("Fork failed");
	}
	else
	{
	wait(NULL);
	}
}
