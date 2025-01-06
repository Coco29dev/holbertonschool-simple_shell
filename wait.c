#include "shell.h"


/**
 * main - fork & wait example
 *
 * Return: Always 0.
 */
int main(void)
{
pid_t child_pid;
int status;
child_pid = fork();
if (child_pid == -1)
{
perror("Error:");
return (1);
}
if (child_pid == 0)
{
printf("Je suis en execution\n");
sleep(3);
}
else
{
wait(&status);
printf("Je viens de terminer\n");
}
return (0);
}
