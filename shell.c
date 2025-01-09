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
pid_t pid = fork(); /* Cree un processus fils avec fork() */
if (pid == -1) /* Si fork echoue */
{
perror("fork failed"); /* Affiche un message d'erreur */
return; /* Sort de la fonction */
}
if (pid == 0) /* Code execute par le processus fils */
{
char *cmd_path = NULL;
if (strchr(argv[0], '/') == NULL) /* Si la commande ne contient pas de '/' */
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
cmd_path = strdup(argv[0]); /* Copie le chemin complet de la commande */
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
if (nchars_read == -1) /* Si la lecture echoue (fin de fichier ou erreur) */
{
return (0); /* Retourne 0 pour indiquer une erreur ou fin de fichier */
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
lineptr_copy = strdup(lineptr); /* Cree une copie de la ligne d'entree */
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
/**
 * main - The main shell loop that reads commands and executes them.
 * This function displays the prompt, reads user input, tokenizes the command,
 * and then executes it.
 * Return: 0
 */
int main(void)
{
char *lineptr = NULL; /* Pointeur pour stocker ligne entree d'utilisateur */
char **cmd_args; /* Tableau pour les arguments de la commande */
size_t n = 0; /* Taille allouee pour la ligne d'entree */
int num_tokens; /* Nombre de tokens apres la tokenisation de la ligne */
int first_run = 1; /* Variable pour verifier si c'est la premiere execution */
int is_interactive = isatty(STDIN_FILENO); /* Verifie si entree interactive */
while (1) /* Boucle principale du shell */
{
if (is_interactive && (first_run || lineptr[0] != '\0'))
{
printf(PROMPT); /* Affiche le prompt si l'entree est interactive */
first_run = 0; /* Met a jour la variable de premiere execution */
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
if (handle_builtin(cmd_args)) /* Si la commande est une commande interne */
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
