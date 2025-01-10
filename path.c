#include "shell.h"
/**
 *find_command_in_path - rechercher fichier executable dans repertoire listes
 *@cmd : Le nom de la commande a rechercher
 *Return: chemin complet de la commande si elle est trouvee, sinon NULL
 */
char *find_command_in_path(char *cmd)
{
	char *path = getenv("PATH"); /* Recupere variable environnement PATH */
	char *path_copy, *dir, *full_path; /* Declare pointers pour la copie */
					/* du PATH, repertoire et full path */
	size_t len; /* Variable pour la longueur du chemin complet */

	if (!path) /* Verifie si la variable PATH est NULL */
	return (NULL); /* Si PATH est NULL, retourne NULL */
	path_copy = strdup(path); /* Cree une copie de la variable PATH */
	if (!path_copy) /* Si la copie echoue, retourne NULL */
	return (NULL);
	dir = strtok(path_copy, ":"); /* Divise PATH separe par ":" */
	while (dir != NULL) /* Tant qu'il y a des repertoires a parcourir */
	{
		len = strlen(dir) + strlen(cmd) + 2; /* Calcul taille totale */
						/* necessaire pour full path */
		full_path = malloc(len); /* Alloue memoire pour full path */
		if (!full_path) /* Si allocation echoue libere copie de PATH */
	{
		free(path_copy);
		return (NULL); /* et retourne NULL */
	}
	snprintf(full_path, len, "%s/%s", dir, cmd); /* Concatene repertoire */
						/* avec nom de la commande */
	if (access(full_path, X_OK) == 0) /* Verifie si fichier executable */
	{
		free(path_copy); /* Libere la copie de PATH */
		return (full_path); /* Retourne le chemin complet si la */
					/* commande trouvee et executable */
	}
	free(full_path); /* Si la commande n'est pas trouvee, libere le chemin */
	dir = strtok(NULL, ":"); /* Passe au repertoire suivant dans PATH */
	}
	free(path_copy); /* Libere la copie de PATH apres avoir parcouru */
			/* tous les repertoires */
	return (NULL); /* Si la commande n'est pas trouvee, retourne NULL */
}
