#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

extern char **environ;

char **tokenize_input(char *lineptr, int *num_tokens);
int read_input(char **lineptr, size_t *n);
void execmd(char **argv);
char *find_command_in_path(char *cmd);
int handle_builtin(char **cmd_args);
void env_builtin(void);
void cmd_exit(char *cmd);

#endif
