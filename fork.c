#include "shell.h"

/**
 * main - main
 * Return: 0/1
 */
int main(void)
{
pid_t pid = fork();
if (pid == -1)
{
perror("fork null");
return (1);
}
else if (pid == 0)
{
printf("Je suis le processus fils, mon PID est %d\n", getpid());
}
else
{
printf("Je suis le processus parent, le PID du fils est %d\n", pid);
}
return (0);
}
