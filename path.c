#include "shell.h"
/**
 *find_command_in_path - rechercher fichier executable dans repertoire listes
 *@cmd : Le nom de la commande a rechercher
 *Return: chemin complet de la commande si elle est trouvee, sinon NULL
 */
char *find_command_in_path(char *cmd)
{
	char *path = getenv("PATH");/*recupere variable env PATH*/
	char *path_copy, *dir, *full_path;
	size_t len;

	if (!path)/*si path pas definie retourne NULL*/
	return (NULL);
	path_copy = strdup(path);/*creation copie PATH pour la modifier*/
	if (!path_copy)/*si allocation echoue retourne NULL*/
	return (NULL);
	/*On commence a separer PATH en repertoires individuels*/
	dir = strtok(path_copy, ":");
	while (dir != NULL)/*on parcourt tous les repertoires de PATH*/
	{
		/*Calcul longueur necessaire pour chemin complet*/
		len = strlen(dir) + strlen(cmd) + 2;/*+2 pour le / et le \0*/
		full_path = malloc(len);/*allocation memoire pour chemin full*/
		if (!full_path)/*si allocation echoue*/
	{
		free(path_copy);/*liberation memoire de la copie de PATH*/
		return (NULL);
	}
	/*construction du chemin complet : repertoire + / + commande*/
	snprintf(full_path, len, "%s/%s", dir, cmd);
	if (access(full_path, X_OK) == 0)/*verification si fichier executable*/
	{
		free(path_copy);/*liberation memoire copie de PATH*/
		return (full_path);
		/*retourne chemin complet si fichier executable*/
	}
	free(full_path);
	/*liberation memoire allouee pour full path si commande non trouvee*/
	dir = strtok(NULL, ":");/*passage au repertoire suivant dans PATH*/
	}
	free(path_copy);
	/*liberer memoire copie de PATH et retour NULL si cmd non trouvee*/
	return (NULL);
}
