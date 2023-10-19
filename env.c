#include "shell.h"

/**
 * display_environment - function to print the current environment.
 * @info: Structure containing potential arguments, used to maintain a constant function prototype.
 *
 * Return: Always returns 0
 */
int display_environment(info_t *info)
{
    print_list_strings(info->envv);
    return 0;
}

/**
 * get_environment_variable - function to retrieve the value of an environment variable.
 * @info: Structure containing potential arguments, used to maintain a constant function prototype.
 * @name: The name of the environment variable to retrieve.
 *
 * Return: The value of the environment variable.
 */
char *get_environment_variable(info_t *info, const char *name)
{
    list_t *nodes = info->envv;
    char *value;

    while (nodes)
    {
        value = start_with(nodes->str, name);
        if (value && *value)
            return value;
        nodes = nodes->next;
    }
    return NULL;
}

/**
 * set_environment_variable - function to initialize a new environment variable or modify an existing one.
 * @info: Structure containing potential arguments, used to maintain a constant function prototype.
 *
 * Return: Always returns 0
 */
int set_environment_variable(info_t *info)
{
    if (info->argc != 3)
    {
        eputs("Incorrect number of arguments\n");
        return 1;
    }
    if (setenv(info, info->argv[1], info->argv[2]))
        return 0;
    return 1;
}

/**
 * unset_environment_variable - function to remove an environment variable.
 * @info: Structure containing potential arguments, used to maintain a constant function prototype.
 *
 * Return: Always returns 0
 */
int unset_environment_variable(info_t *info)
{
    int i;

    if (info->argc == 1)
    {
        eputs("Too few arguments.\n");
        return 1;
    }
    for (i = 1; i <= info->argc; i++)
        unsetenv(info, info->argv[i]);

    return 0;
}

/**
 * populate_environment_list - function to populate the environment linked list.
 * @info: Structure containing potential arguments, used to maintain a constant function prototype.
 *
 * Return: Always returns 0
 */
int populate_environment_list(info_t *info)
{
    list_t *nodes = NULL;
    size_t i;

    for (i = 0; environ[i]; i++)
        add_node_end(&nodes, environ[i], 0);
    info->envv = nodes;
    return 0;
}

