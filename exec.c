#include "shell.h"

/**
 * execmd - Executes a command using execve.
 * @argv: The argument array of the command.
 * This function forks a new process and executes the command.
 * If the command contains a full path, execve is called directly.
 * Otherwise, it outputs an error message.
 */
void execmd(char **argv)
{
	pid_t pid = fork(); /* Cree un processus fils avec fork() */
	if (pid == -1) /* Si fork echoue */
	{
		perror("fork failed"); /* Affiche un message d'erreur */
		return; /* Sort de la fonction */
	}
	if (pid == 0) /* Code execute par le processus fils */
	{
		char *cmd_path = NULL;
		if (strchr(argv[0], '/') == NULL) /* Si cmd contient pas '/' */
		{
		cmd_path = find_command_in_path(argv[0]);
		/* Recherche le chemin de la commande dans PATH */
		if (cmd_path == NULL) /* Si la commande n'est pas trouvee */
		{
			fprintf(stderr, "./hsh: No such file or directory\n");
			/* Affiche une erreur */
			exit(1); /* Quitte avec un code d'erreur */
		}
		}
		else /* Si la commande contient un chemin absolu ou relatif */
		{
		cmd_path = strdup(argv[0]); /* Copie full path de la cmd */
		}
		if (execve(cmd_path, argv, NULL) == -1)
		/* Tente d'executer la commande avec execve */
		{
		fprintf(stderr, "./hsh: No such file or directory\n");
		exit(1); /* Quitte avec un code d'erreur */
		}
	}
	else /* Code execute par le processus parent */
	{
		wait(NULL); /* Attend que le processus fils se termine */
	}
}
