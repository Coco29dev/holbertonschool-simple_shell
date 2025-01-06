#include "shell.h"

/**
 * print_ppid - PPID
 *
 * Return: Always 0.
 */
void print_ppid(void)
{
pid_t my_pid;
my_pid = getppid();
printf("The PPID is : %u\n", my_pid);
}
