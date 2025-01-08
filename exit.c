#include "shell.h"

/**
 * exit - exit shell
 * @cmd: commande
 * Return: nothing
 */
void cmd_exit(char *cmd)
{
if (strncmp(cmd, "exit", strlen(cmd)) == 0)
{
exit(EXIT_SUCCESS);
}
}
