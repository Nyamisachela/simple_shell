#ifndef HELPERS_H
#define HELPERS_H

/* Prompt to be printed */
#define PROMPT_MSG "Whew:) " /* Needed to work with signal */

/* Resume from the unused attribute */
#define UNUSED __attribute__((unused))

/* Buffer size for each read call in _getline */
#define BUFFER_SIZE 1024

/****** FORMATTED STRINGS FOR HELP BUILT-IN ******/

#define HELP_CD_MSG "cd=\n"\
"cd:\tcd [dir]\n\n"\
"Change the shell working directory.\n\n"\
"If no argument is given to cd, the command will be interpreted as cd $HOME.\n"\
"If the argument is '-', the command will be interpreted as cd $OLDPWD.\n\n"

#define HELP_EXIT_MSG "exit=\n"\
"exit:\texit [STATUS]\n\n"\
"Exit of the simple-shell.\n\n"\
"Exits the shell with a status of N. If N is omitted, the exit status is that of the last command executed.\n\n"

#define HELP_ENV_MSG "env=\n"\
"env:\tenv \n\n"\
"Print environment.\n\n"\
"The env command will print a complete list of environment variables.\n\n"

#define HELP_SETENV_MSG "setenv=\n"\
"setenv:\tsetenv VARIABLE VALUE\n\n"\
"Change or add an environment variable.\n\n"\
"Initialize a new environment variable or modify an existing one.\n"\
"When there is an incorrect number of arguments, print an error message.\n\n"

#define HELP_UNSETENV_MSG "unsetenv=\n"\
"unsetenv:\tunsetenv VARIABLE\n\n"\
"The unsetenv function deletes one variable from the environment.\n\n"\
"When there is an incorrect number of arguments, print an error message.\n\n"

#define HELP_MSG "help=\n"\
"help:\thelp [BUILTIN_NAME]\n\n"\
"Display information about builtin commands.\n\n"\
"Displays brief summaries of builtin commands. If BUILTIN_NAME is specified, gives detailed help on all commands matching BUILTIN_NAME; otherwise, the list of help topics is printed. BUILTIN_NAME list:\n\n"\
"cd\t[dir]\n"\
"exit\t[status]\n"\
"env\n"\
"setenv\t[variable value]\n"\
"unset\t[variable]\n"\
"help\t[built_name]\n\n"

#endif
