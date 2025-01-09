#include "shell.h"
/**
 *find_command_in_path - rechercher fichier executable dans repertoire listes
 *@cmd : Le nom de la commande a rechercher
 *Return: chemin complet de la commande si elle est trouvee, sinon NULL
 */
char *find_command_in_path(char *cmd)
{
	char *path = getenv("PATH"); /* Recupere variable d'environnement PATH */
	char *path_copy, *dir, *full_path; /* Declare des pointeurs pour la copie */
						/* du PATH, le repertoire et le chemin complet */
	size_t len; /* Variable pour la longueur du chemin complet */

	if (!path) /* Verifie si la variable PATH est NULL */
	return (NULL); /* Si PATH est NULL, retourne NULL */
	path_copy = strdup(path); /* Cree une copie de la variable PATH */
	if (!path_copy) /* Si la copie echoue, retourne NULL */
	return (NULL);
	dir = strtok(path_copy, ":"); /* Divise PATH en repertoire separes par ":" */
	while (dir != NULL) /* Tant qu'il y a des repertoires a parcourir */
	{
		len = strlen(dir) + strlen(cmd) + 2; /* Calcule la taille totale */
							/* necessaire pour le chemin complet */
		full_path = malloc(len); /* Alloue de la memoire pour le chemin complet */
		if (!full_path) /* Si l'allocation echoue, libere la copie de PATH */
	{
		free(path_copy);
		return (NULL); /* et retourne NULL */
	}
	snprintf(full_path, len, "%s/%s", dir, cmd); /* Concatene le repertoire */
							/* avec le nom de la commande */
	if (access(full_path, X_OK) == 0) /* Verifie si le fichier est executable */
	{
		free(path_copy); /* Libere la copie de PATH */
		return (full_path); /* Retourne le chemin complet si la */
					/* commande est trouvee et executable */
	}
	free(full_path); /* Si la commande n'est pas trouvee, libere le chemin */
	dir = strtok(NULL, ":"); /* Passe au repertoire suivant dans PATH */
	}
	free(path_copy); /* Libere la copie de PATH apres avoir parcouru */
			/* tous les repertoires */
	return (NULL); /* Si la commande n'est pas trouvee, retourne NULL */
}
