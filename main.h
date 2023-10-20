#ifndef MAIN_H
#define MAIN_H

#include <stdio.h> /* Standard input-output library for printf */
#include <unistd.h>  /* Library for fork, execve */
#include <stdlib.h> /* Standard library for general functions */
#include <string.h>  /* Library for string manipulation, strtok */
#include <stddef.h> /* Standard definitions for data types and NULL */
#include <errno.h> /* Library for error handling, errno, and perror */
#include <sys/types.h>  /* Library for data types, e.g., pid_t */
#include <sys/wait.h> /* Library for wait functions */
#include <sys/stat.h> /* Library for file status and information */
#include <signal.h> /* Library for signal management */
#include <fcntl.h> /* Library for file operations */

/************* MACROS **************/

#include "macros.h" /* Include macros for message help and prompt */

/******* STRUCTURES ********/

/**
 * struct info - Structure for program data
 * @program_name: Name of the executable
 * @input_line: Pointer to the input read from _getline
 * @command_name: Pointer to the first command typed by the user
 * @exec_counter: Number of executed commands
 * @file_descriptor: File descriptor for input of commands
 * @tokens: Pointer to an array of tokenized input
 * @env: Copy of the environment variables
 * @alias_list: Array of pointers with aliases
 */
typedef struct info
{
    char *program_name;
    char *input_line;
    char *command_name;
    int exec_counter;
    int file_descriptor;
    char **tokens;
    char **env;
    char **alias_list;
} data_of_program;

/**
 * struct builtins - Structure for built-in commands
 * @builtin: Name of the built-in command
 * @function: Associated function to be called for each built-in
 */
typedef struct builtins
{
    char *builtin;
    int (*function)(data_of_program *data);
} builtins;

/***** MAIN FUNCTIONS ******/

/* Initialize the struct with program data */
void initialize_data(data_of_program *data, int argc, char *argv[], char **env);

/* Create an infinite loop that displays the prompt */
void our_prompt(char *prompt, data_of_program *data);

/* Print the prompt in a new line */
void handle_ctrl_c(int operation UNUSED);

/* Read one line from standard input */
int _getline(data_of_program *data);

/* Split each line by logical operators if they exist */
int check_logic_ops(char *array_commands[], int i, char array_operators[]);

/* Expand variables */
void expand_variables(data_of_program *data);

/* Expand aliases */
void expand_alias(data_of_program *data);

/* Append a string to the end of the buffer */
int buffer_add(char *buffer, char *str_to_add);

/* Separate a string into tokens using a specified delimiter */
void tokenize(data_of_program *data);

/* Create a pointer to a part of a string */
char *_strtok(char *line, char *delim);

/* Execute a command with its entire path */
int execute(data_of_program *data);

/* Match a built-in command and execute it */
int builtins_list(data_of_program *data);

/* Create an array of path directories */
char **tokenize_path(data_of_program *data);

/* Search for a program in the PATH */
int find_program(data_of_program *data);

/****** HELPERS FOR MEMORY MANAGEMENT ******/

/* Free memory for directories */
void free_array_of_pointers(char **directories);

/* Free the fields needed in each loop */
void free_recurrent_data(data_of_program *data);

/* Free all fields of the data */
void free_all_data(data_of_program *data);

/****** BUILT-IN COMMANDS ******/

/* Close the shell */
int builtin_exit(data_of_program *data);

/* Change the current directory */
int builtin_cd(data_of_program *data);

/* Set the working directory */
int set_work_directory(data_of_program *data, char *new_dir);

/* Display help information */
int builtin_help(data_of_program *data);

/* Set, unset, and show aliases */
int builtin_alias(data_of_program *data);

/* Show the environment where the shell runs */
int builtin_env(data_of_program *data);

/* Create or override an environment variable */
int builtin_set_env(data_of_program *data);

/* Delete an environment variable */
int builtin_unset_env(data_of_program *data);

/******** HELPERS FOR ENVIRONMENT VARIABLES MANAGEMENT ********/

/* Get the value of an environment variable */
char *env_get_key(char *name, data_of_program *data);

/* Overwrite the value of an environment variable */
int env_set_key(char *key, char *value, data_of_program *data);

/* Remove a key from the environment */
int env_remove_key(char *key, data_of_program *data);

/* Print the current environment */
void print_environ(data_of_program *data);

/****** HELPERS FOR PRINTING ******/

/* Print a string to standard output */
int _print(char *string);

/* Print a string to standard error */
int _printe(char *string);

/* Print a string to standard error with an error code */
int _print_error(int errorcode, data_of_program *data);

/************ HELPERS FOR STRING MANAGEMENT ***********/

/* Count the number of characters in a string */
int str_length(char *string);

/* Duplicate a string */
char *str_duplicate(char *string);

/* Compare two strings */
int str_compare(char *string1, char *string2, int number);

/* Concatenate two strings */
char *str_concat(char *string1, char *string2);

/* Reverse a string */
void str_reverse(char *string);

/****** HELPERS FOR NUMBERS MANAGEMENT **********/

/* Convert a long integer to a string */
void long_to_string(long number, char *string, int base);

/* Convert a string to an integer */
int _atoi(char *s);

/* Count the occurrences of a character in a string */
int count_characters(char *string, char *character);

/****** ALIAS MANAGEMENT ******/

/* Print the list of aliases */
int print_alias(data_of_program *data, char *alias);

/* Get the alias name */
char *get_alias(data_of_program *data, char *alias);

/* Set the alias name */
int set_alias(char *alias_string, data_of_program *data);

#endif /* MAIN_H */

