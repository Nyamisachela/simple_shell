#ifndef SHELL_H_
#define SHELL_H_

/* Header files to include */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define BUFFER_SIZE 1024

/* Function Prototypes */
int main(void);
char **split_input(char *);
int arg_count(char **);
#endif
