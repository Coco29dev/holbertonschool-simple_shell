#include "shell.h"

/**
 * cmd_exit - exit shell
 * @cmd_args: commande
 * Return: nothing
 */
void cmd_exit(char **cmd_args)
{
if (cmd_args != NULL && cmd_args[0] != NULL
&& strcmp(cmd_args[0], "exit") == 0)
{
exit(EXIT_SUCCESS);
}
}
