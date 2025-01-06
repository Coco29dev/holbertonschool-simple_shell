#include "shell.h"

/**
 * fork_example - main
 * Return: 0/1
 */
void fork_example(void)
{
pid_t pid = fork();
if (pid == -1)
{
perror("fork null");
}
else if (pid == 0)
{
printf("Je suis le processus fils, mon PID est %d\n", getpid());
}
else
{
printf("Je suis le processus parent, le PID du fils est %d\n", pid);
}
}
