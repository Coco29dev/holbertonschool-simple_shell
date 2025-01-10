#include "shell.h"
/**
 * main - The main shell loop that reads commands and executes them.
 * This function displays the prompt, reads user input, tokenizes the command,
 * and then executes it.
 * Return: 0
 */
int main(void)
{
	char *lineptr = NULL; /* Pointeur pour stocker ligne entree user */
	char **cmd_args; /* Tableau pour les arguments de la commande */
	size_t n = 0; /* Taille allouee pour la ligne d'entree */
	int num_tokens; /* Nombre de tokens apres la tokenisation de la ligne*/
	int first_run = 1; /* Variable pour verifier si premiere execution */
	int is_interactive = isatty(STDIN_FILENO); /* Verifie entree interac*/

	while (1) /* Boucle principale du shell */
	{
	if (is_interactive && (first_run || lineptr[0] != '\0'))
	{
		printf(PROMPT); /* Affiche prompt si entree est interactive */
		first_run = 0; /* Met a jour variable de premiere execution */
	}
	if (!read_input(&lineptr, &n)) /* Lit l'entree de l'utilisateur */
	{
		if (is_interactive) /* Si mode interactif */
		printf("\n"); /* Affiche une nouvelle ligne */
		break; /* Quitte la boucle si la lecture echoue */
	}
	cmd_args = tokenize_input(lineptr, &num_tokens);
	if (!cmd_args) /* Si la tokenisation echoue */
	continue; /* Passe a l'iteration suivante de la boucle */
	if (cmd_args[0] == NULL) /* Si la ligne d'entree est vide */
	{
		free(cmd_args); /* Libere la memoire allouee pour cmd_args */
		continue; /* Passe a l'iteration suivante de la boucle */
	}
	if (handle_builtin(cmd_args)) /* Si commande est commande interne */
	{
		free(cmd_args); /* Libere la memoire allouee pour cmd_args */
		break; /* Quitte la boucle */
	}
	execmd(cmd_args); /* Execute la commande avec execmd */
	free(cmd_args); /* Libere la memoire allouee pour cmd_args */
	}
	free(lineptr); /* Libere la memoire allouee pour la ligne d'entree */
	return (0); /* Retourne 0 pour indiquer la fin normale du programme */
}
