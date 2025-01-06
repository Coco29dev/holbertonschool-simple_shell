#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

void execute_command(char *cmd);
void execute_command(char *cmd);
void print_pid(void);
void print_ppid(void);
void fork_example(void);
void wait_example(void);

#endif
