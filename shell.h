#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

/* constant variables */
#define MAX_INPUT_SIZE 1024

/* function prototypes */
void display_prompt(void);
void read_user_input(char *, size_t, ssize_t *);
void execute_command(char *);

#endif
