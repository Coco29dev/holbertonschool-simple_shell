#include "shell.h"

void print_pid(void)
{
    pid_t my_pid = getpid();
    printf("The PID is: %u\n", my_pid);
}
