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
char *cmd_path = NULL;
pid_t pid;
if (strchr(argv[0], '/') == NULL)
{
cmd_path = find_command_in_path(argv[0]);
if (cmd_path == NULL)
{
fprintf(stderr, "./hsh: No such file or directory\n");
return;
}
}
else
{
cmd_path = strdup(argv[0]);
}
pid = fork();
if (pid == -1)
{
perror("fork failed");
free(cmd_path);
return;
}
if (pid == 0)
{
if (execve(cmd_path, argv, NULL) == -1)
{
fprintf(stderr, "./hsh: No such file or directory\n");
free(cmd_path);
exit(1);
}
}
else
{
wait(NULL);
}
free(cmd_path);
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
if (nchars_read == -1)
{
return (0);
}
return (1);
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
lineptr_copy = strdup(lineptr);
if (!lineptr_copy)
{
perror("malloc failed");
return (NULL);
}
*num_tokens = 0;
token = strtok(lineptr_copy, DELIM);
while (token != NULL)
{
(*num_tokens)++;
token = strtok(NULL, DELIM);
}
cmd_args = malloc(sizeof(char *) * (*num_tokens + 1));
if (!cmd_args)
{
perror("malloc failed for cmd_args");
free(lineptr_copy);
return (NULL);
}
token = strtok(lineptr, DELIM);
while (token != NULL)
{
cmd_args[i++] = token;
token = strtok(NULL, DELIM);
}
cmd_args[i] = NULL;
free(lineptr_copy);
return (cmd_args);
}
/**
 * main - The main shell loop that reads commands and executes them.
 * This function displays the prompt, reads user input, tokenizes the command,
 * and then executes it.
 * Return: 0
 */
int main(void)
{
char *lineptr = NULL;
char **cmd_args;
size_t n = 0;
int num_tokens;
int first_run = 1;
int is_interactive = isatty(STDIN_FILENO);
while (1)
{
if (is_interactive && (first_run || lineptr[0] != '\0'))
{
printf(PROMPT);
first_run = 0;
}
if (!read_input(&lineptr, &n))
{
if (is_interactive)
printf("\n");
break;
}
cmd_args = tokenize_input(lineptr, &num_tokens);
if (!cmd_args)
continue;
if (cmd_args[0] == NULL)
{
free(cmd_args);
continue;
}
if (handle_builtin(cmd_args))
{
free(cmd_args);
break;
}
execmd(cmd_args);
free(cmd_args);
}
free(lineptr);
return (0);
}
