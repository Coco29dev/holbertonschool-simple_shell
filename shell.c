#include "shell.h"

/**
 * main - main
 * Return: 0
 */


#define PROMPT "($) "

int main(void)
{
	char *cmd = NULL;
	size_t len = 0;
	ssize_t nread;

	while (1)

	{
	if (isatty(fileno(stdin)))
	{
	printf("%s", PROMPT);
	}
	nread = getline(&cmd, &len, stdin);

	if (nread == -1)
	{
		if (feof(stdin))
		{
		printf("\n");
		break;
	}
		else
	{
		continue;
	}
	}

	cmd[strcspn(cmd, "\n")] = 0;

	if (strlen(cmd) > 0)
	{
	execute_command(cmd);
	}
	}
	free(cmd);
	return (0);
}
