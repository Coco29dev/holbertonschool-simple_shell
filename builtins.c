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
	/* Pointeur pour parcourir les variables d'environnement */

	while (*env != NULL)
	/* Tant que l'element actuel de l'environnement n'est pas NULL */
	{
		printf("%s\n", *env); /* Affiche la variable d'environnement courante */
		env++; /* Passee a la variable d'environnement suivante */
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
	/* Si les arguments sont vides */
	return (0); /* Retourne 0 si aucun argument n'est fourni */

	if (strcmp(cmd_args[0], "env") == 0)
	/* Si la commande est "env" */
	{
		env_builtin(); /* Appelle la fonction pour afficher les variables d'env */
		return (1); /* Retourne 1 pour indiquer que la commande a ete traitee */
	}

	if (strcmp(cmd_args[0], "exit") == 0)
	/* Si la commande est "exit" */
	{
	cmd_exit(); /* Appelle la fonction pour quitter le shell */
	return (1); /* Retourne 1 pour indiquer que la commande a ete traitee */
	}

	return (0); /* Retourne 0 si la commande n'est pas une commande interne */
}
