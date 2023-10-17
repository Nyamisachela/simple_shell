#ifndef SHELL_H_
#define SHELL_H_

/* Header files to include */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>

#define BUFFER_SIZE 1024

/* Function Prototypes */
int main(int, char **);
char **split_input(char *);
int arg_count(char **);
void execute(char **);
char *get_path(char *command);
void print_env(void);

/* external variables */
extern char **environ;
#endif
