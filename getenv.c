#include "shell.h"

/**
 * get_environ_copy - returns a copy of the environment variables as a string array.
 * @info: Structure containing potential arguments. Used to maintain constant function prototype.
 *
 * Return: The string array copy of environment variables.
 */
char **get_environ_copy(info_t *info)
{
    if (!info->environ_copy || info->envv_changed)
    {
        info->environ_copy = list_to_string(info->envv);
        info->envv_changed = 0;
    }

    return info->environ_copy;
}

/**
 * unset_environment_variable - Remove an environment variable.
 * @info: Structure containing potential arguments. Used to maintain constant function prototype.
 * @variable: The environment variable property to remove.
 *
 * Return: 1 if the variable is deleted, 0 otherwise.
 */
int unset_environment_variable(info_t *info, char *variable)
{
    list_t *nodes = info->envv;
    size_t index = 0;
    char *equals_position;

    if (!nodes || !variable)
        return 0;

    while (nodes)
    {
        equals_position = start_with(nodes->strr, variable);
        if (equals_position && *equals_position == '=')
        {
            info->envv_changed = delete_node_at_index(&(info->envv), index);
            index = 0;
            nodes = info->envv;
            continue;
        }
        nodes = nodes->next;
        index++;
    }
    return info->envv_changed;
}

/**
 * set_environment_variable - Initialize a new environment variable or modify an existing one.
 * @info: Structure containing potential arguments. Used to maintain constant function prototype.
 * @variable: The environment variable property.
 * @value: The environment variable value.
 *
 * Return: 0 on success, 1 on error.
 */
int set_environment_variable(info_t *info, char *variable, char *value)
{
    char *buffer = NULL;
    list_t *nodes;
    char *equals_position;

    if (!variable || !value)
        return 1;

    buffer = malloc(strlen(variable) + strlen(value) + 2);
    if (!buffer)
        return 1;
    strcpy(buffer, variable);
    strcat(buffer, "=");
    strcat(buffer, value);
    nodes = info->envv;

    while (nodes)
    {
        equals_position = start_with(nodes->strr, variable);
        if (equals_position && *equals_position == '=')
        {
            free(nodes->strr);
            nodes->strr = buffer;
            info->envv_changed = 1;
            return 0;
        }
        nodes = nodes->next;
    }
    add_node_end(&(info->envv), buffer, 0);
    free(buffer);
    info->envv_changed = 1;
    return 0;
}

