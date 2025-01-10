#include "shell.h"

/**
 * read_input - Reads a line of input from the user.
 * @lineptr: A pointer to the buffer where the line will be stored.
 * @n: The size of the buffer.
 * Return: 1 on success, 0 if EOF (Ctrl+D) or error.
 */
int read_input(char **lineptr, size_t *n)
{
	ssize_t nchars_read = getline(lineptr, n, stdin);
	/* Lit une ligne depuis stdin */
	if (nchars_read == -1) /* Si lecture echoue (fin fichier ou erreur) */
	{
		return (0); /* Return 0 pour indiquer erreur ou fin fichier */
	}
	return (1); /* Retourne 1 si la lecture a reussi */
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
	/* Declare des pointeurs pour le token et la copie de la ligne */
	char **cmd_args;
	/* Declare un tableau de pointeurs pour les arguments de la commande */
	int i = 0; /* Compteur pour les arguments du tableau */
	lineptr_copy = strdup(lineptr); /* Cree copie de la ligne d'entree */

	if (!lineptr_copy) /* Si la copie echoue */
	{
		perror("malloc failed"); /* Affiche une erreur */
		return (NULL); /* Retourne NULL en cas d'erreur */
	}
	*num_tokens = 0; /* Initialise le nombre de tokens a 0 */
	token = strtok(lineptr_copy, DELIM);
	/* Divise la ligne en tokens en utilisant DELIM comme separateur */
	while (token != NULL) /* Tant qu'il y a des tokens */
	{
		(*num_tokens)++; /* Incremente le nombre de tokens */
		token = strtok(NULL, DELIM); /* Passe au token suivant */
	}
	cmd_args = malloc(sizeof(char *) * (*num_tokens + 1));
	/* Alloue de la memoire pour le tableau d'arguments */
	if (!cmd_args) /* Si l'allocation echoue */
	{
		perror("malloc failed for cmd_args"); /* Affiche une erreur */
		free(lineptr_copy); /* Libere la copie de la ligne */
		return (NULL); /* Retourne NULL en cas d'erreur */
	}
	token = strtok(lineptr, DELIM);
	/* Recommence la tokenisation de la ligne d'origine */
	while (token != NULL) /* Tant qu'il y a des tokens */
	{
	cmd_args[i++] = token; /* Ajoute le token au tableau des arguments */
	token = strtok(NULL, DELIM); /* Passe au token suivant */
	}
	cmd_args[i] = NULL;
	/* Termine le tableau avec un pointeur NULL pour marquer la fin */
	free(lineptr_copy); /* Libere la copie de la ligne d'entree */
	return (cmd_args); /* Retourne le tableau d'arguments */
}
