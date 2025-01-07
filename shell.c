#include "shell.h"

#define PROMPT "($) "
#define DELIM " \n"

/**
 * execmd - Executes a command using execve.
 * @argv: The argument array of the command.
 * This function forks a new process and executes the command.
 * If the command contains a full path, execve is called directly.
 * Otherwise, it outputs an error message.
 */
void execmd(char **argv)
{
	pid_t pid = fork();/*creer nouveau processus*/
	if (pid == -1)
	{
		perror("fork failed");/*si fork echoue*/
		return;
	}
	if (pid == 0)/*processus enfant*/
	{
		if (strchr(argv[0], '/') != NULL)/*si chemin est complet*/
	{
		if (execve(argv[0], argv, NULL) == -1)/*execute la commande*/
		{
		/*si execve echoue*/
		fprintf(stderr, "./hsh: No such file or directory\n");
		exit(1);
		}
	}
	else
	{
		/*si la commande n'a pas de chemin complet*/
		fprintf(stderr, "./hsh: No such file or directory\n");
	exit(1);
	}
	}
	else
	{
	wait(NULL);
	}
}
/**
 * read_input - Reads a line of input from the user.
 * @lineptr: A pointer to the buffer where the line will be stored.
 * @n: The size of the buffer.
 * Return: 1 on success, 0 if EOF (Ctrl+D) or error.
 */
int read_input(char **lineptr, size_t *n)
{
	/*lecture de la ligne*/
	ssize_t nchars_read = getline(lineptr, n, stdin);

	if (nchars_read == -1)/*si erreur ou EOF rencontree*/
	{
	return (0);/*retourne 0 pour signaler erreur ou EOF*/
	}
	return (1);/*retourne 1 si lecture reussie*/
}

/**
 * tokenize_input - Tokenizes the command line into an argument array.
 * @lineptr: The command line to tokenize.
 * @num_tokens: The number of tokens extracted.
 * This function splits the command line into individual words.
 * Return: a dynamically allocated array of strings (NULL-terminated).
 */
char **tokenize_input(char *lineptr, int *num_tokens)
{
	char *token, *lineptr_copy;
	char **cmd_args;
	int i = 0;

	lineptr_copy = strdup(lineptr);/*copie la ligne pour eviter modif*/
	if (!lineptr_copy)/*si copie echoue*/
	{
		perror("malloc failed");/*erreur de malloc*/
		return (NULL);
	}
	*num_tokens = 0;/*initialise nombre de tokens*/
	token = strtok(lineptr_copy, DELIM);/*on commence a separer la ligne*/
	while (token != NULL)
	{
		(*num_tokens)++;/*incrementer nombre de tokens*/
		token = strtok(NULL, DELIM);/*obtenir token suivant*/
	}
	/*allouer memoire pour tableau d'arguments*/
	cmd_args = malloc(sizeof(char *) * (*num_tokens + 1));
	if (!cmd_args)/*si allocation echoue*/
	{
		/*erreur de malloc pour cmd_args*/
		perror("malloc failed for cmd_args");
		free(lineptr_copy);/*liberer memoire allouee pour copie ligne*/
		return (NULL);
	}
	token = strtok(lineptr, DELIM);/*reprendre decoupage ligne originale*/
	while (token != NULL)
	{
		cmd_args[i++] = token;/*ajouter chaque token dans tableau*/
		token = strtok(NULL, DELIM);/*obtenir token suivant*/
	}
	cmd_args[i] = NULL;/*terminer tableau avec NULL*/
	free(lineptr_copy);/*liberer memoire de la copie de la ligne*/
	return (cmd_args);/*retourner tableau d'arguments*/
}

/**
 * main - The main shell loop that reads commands and executes them.
 * This function displays the prompt, reads user input, tokenizes the command,
 * and then executes it.
 * Return: 0
 */
int main(void)
{
	char *lineptr = NULL;/*pointeur vers ligne entree par utilisateur*/
	char **cmd_args;/*tableau pour arguments de la commande*/
	size_t n = 0;/*taille du buffer pour getline*/
	int num_tokens;/*nombre de tokens dans la commande*/
	int first_run = 1;/*indicateur pour savoir si 1ere execution*/
	int is_interactive = isatty(STDIN_FILENO);/*verifie si entree interac*/

	while (1)/*boucle infinie pour maintenir shell en fonctionnement*/
	{
	if (is_interactive && (first_run || lineptr[0] != '\0'))
		/*si shell est interactif*/
	{
		printf(PROMPT);/*affiche invite de commande*/
		first_run = 0;/*une fois invite affichee, plus 1ere execution*/
	}
	if (!read_input(&lineptr, &n))/*lecture entree utilisateur*/
	{
		if (is_interactive)
		printf("\n");
		/*affiche saut de ligne si EOF ou erreur en mode interactif*/
		break;/*quitte la boucle si EOF ou erreur*/
	}
	cmd_args = tokenize_input(lineptr, &num_tokens);/*tokenise entree*/
	if (!cmd_args)/*si tokenisation echoue*/
	continue;/*passe a iteration suivante*/
	if (cmd_args[0] == NULL)/*si commande est vide*/
	{
		free(cmd_args);/*libere memoire alloue pour cmd_args*/
		continue;/*passe a iteration suivante*/
	}
	execmd(cmd_args);/*execution commande*/
	free(cmd_args);/*libere memoire allouee pour cmd_args*/
	}
	free(lineptr);/*libere memoire allouee pour ligne entree*/
	return (0);/*fin du programme*/
}
