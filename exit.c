#include "shell.h"

/**
 * exit - exit shell
 * @cmd: commande
 * Return: nothing
 */
void cmd_exit(char *cmd)
{
if (strcmp(cmd, "exit")  == 0)
{
exit(EXIT_SUCCESS);
}
}
