#include "shell.h"
/**
 *find_command_in_path - rechercher fichier executable dans repertoire listes
 *@cmd : Le nom de la commande a rechercher
 *Return: chemin complet de la commande si elle est trouvee, sinon NULL
 */
char *find_command_in_path(char *cmd)
{
	char *path = getenv("PATH");
	char *path_copy, *dir, *full_path;
	size_t len;

	if (!path)
	return (NULL);
	path_copy = strdup(path);
	if (!path_copy)
	return (NULL);
	dir = strtok(path_copy, ":");
	while (dir != NULL)
	{
		len = strlen(dir) + strlen(cmd) + 2;
		full_path = malloc(len);
		if (!full_path)
	{
		free(path_copy);
		return (NULL);
	}
	snprintf(full_path, len, "%s/%s", dir, cmd);
	if (access(full_path, X_OK) == 0)
	{
		free(path_copy);
		return (full_path);
	}
	free(full_path);
	dir = strtok(NULL, ":");
	}
	free(path_copy);
	return (NULL);
}
