# Simple Shell

This project is a shell program developed in C language, providing a simple user interface for executing system commands.

## Description

This program provides an interactive shell that allows users to execute system commands via a command-line interface. 
It supports several core features, including executing basic commands, managing environment variables, and running system commands such as `ls -l`.

## Requirements 

### General

* Allowed editors: vi, vim, emacs
* All your files will be compiled on Ubuntu 20.04 LTS using gcc, using the options -Wall -Werror -Wextra -pedantic -std=gnu89
* All your files should end with a new line
* A `README.md` file, at the root of the folder of the project is mandatory
* Your code should use the Betty style. It will be checked using betty-style.pl and betty-doc.pl
* Your shell should not have any memory leaks
* No more than 5 functions per file
* All your header files should be include guarded
* Use system calls only when you need to (why?)

### List of allowed functions and system calls+

* all functions from string.h
* `access` (man 2 access)
* `chdir` (man 2 chdir)
* `close` (man 2 close)
* `closedir` (man 3 closedir)
* `execve` (man 2 execve)
* `exit` (man 3 exit)
* `_exit` (man 2 _exit)
* `fflush` (man 3 fflush)
* `fork` (man 2 fork)
* `free` (man 3 free)
* `getcwd` (man 3 getcwd)
* `getline` (man 3 getline)
* `getpid` (man 2 getpid)
* `isatty` (man 3 isatty)
* `kill` (man 2 kill)
* `malloc` (man 3 malloc)
* `open` (man 2 open)
* `opendir` (man 3 opendir)
* `perror` (man 3 perror)
* `printf` (man 3 printf)
* `fprintf` (man 3 fprintf)
* `vfprintf` (man 3 vfprintf)
* `sprintf` (man 3 sprintf)
* `putchar` (man 3 putchar)
* `read` (man 2 read)
* `readdir` (man 3 readdir)
* `signal` (man 2 signal)
* `stat` (__xstat) (man 2 stat)
* `lstat` (__lxstat) (man 2 lstat)
* `fstat` (__fxstat) (man 2 fstat)
* `strtok` (man 3 strtok)
* `wait` (man 2 wait)
* `waitpid` (man 2 waitpid)
* `wait3` (man 2 wait3)
* `wait4` (man 2 wait4)
* `write` (man 2 write)

### Tasks

1. - README.md, man, authors.
2. - Betty style code.
3. - Simple shell 0.1 - write a UNIX command line interpreter.
4. - Simple shell 0.2 - handles command lines with arguments.
5. - Simple shell 0.3 - handle path, fork must not be called if the command doesn't exist.
6. - Simple shell 0.4 - implement exit built-in.
7. - Simple shell 1.0 - implement the env built-in.

### Compilation

```bash
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh
```


## Files

* `shell.h` 

Header file defining function prototypes, constants, and external variables for the shell program, including input handling, command execution, and built-in commands.

* `shell.c`

Implements the main shell loop, handling user input, tokenization, command execution, and built-in command handling in an interactive shell.

* `exec.c`

Implements the execmd function to fork a child process, execute a command using execve, and handle errors if the command is not found.

* `input.c`

Implements functions to read user input and tokenize the command line into an array of arguments, handling memory allocation and token parsing.

* `path.c`

Implements the find_command_in_path function to search for an executable command in the directories listed in the PATH environment variable.

* `builtins.c`

Implements built-in shell commands such as `exit` to terminate the program and `env` to print all environment variables, along with handling of these commands.

* `AUTHORS`

Lists the contributors and authors of the project.

* `README.md`

Provides an overview of the shell program and usage instructions.

* `man_1_simple_shell`

The project's manual page, formatted for compatibility with the UNIX man command, provides detailed documentation on how to use the shell, including available commands and options.

## Flowchart

<a href="https://ibb.co/S6jN3V1"><img src="https://i.ibb.co/TwfcgPn/Capture-d-e-cran-2025-01-10-a-12-18-44.png" alt="Capture-d-e-cran-2025-01-10-a-12-18-44" border="0"></a>

## Test

### Interactive mode

<a href="https://ibb.co/bd6gLdx"><img src="https://i.ibb.co/3hTyWhw/Capture-d-e-cran-2025-01-10-a-09-49-59.png" alt="Capture-d-e-cran-2025-01-10-a-09-49-59" border="0"></a>

### Non-interactive mode

<a href="https://ibb.co/bd6gLdx"><img src="https://i.ibb.co/3hTyWhw/Capture-d-e-cran-2025-01-10-a-09-49-59.png" alt="Capture-d-e-cran-2025-01-10-a-09-49-59" border="0"></a>

## Contributors

Corentin Robles

Damien Boulet
