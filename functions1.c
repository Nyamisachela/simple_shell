#include "shell.h"

/**
 * display_history - function to display the command history list, one command per line,
 * preceded by line numbers starting at 0.
 * @info: Structure containing potential arguments, used to maintain a constant function prototype.
 *
 * Return: Always returns 0
 */
int display_history(info_t *info)
{
    print_list(info->_history);
    return 0;
}

/**
 * unset_alias - function to unset an alias by its string representation
 * @info: Parameter to struct
 * @str: The string representation of the alias
 *
 * Return: Always returns 0 on success, 1 on error
 */
int unset_alias(info_t *info, char *str)
{
    char *equal_sign, saved_char;
    int result;

    equal_sign = strchr(str, '=');
    if (!equal_sign)
        return 1;
    saved_char = *equal_sign;
    *equal_sign = '\0';
    result = delete_node_at_index(&(info->alias), get_node_index(info->alias, node_starting_with(info->alias, str, -1)));
    *equal_sign = saved_char;
    return result;
}

/**
 * set_alias - function to set an alias to a string representation
 * @info: The parameter to struct
 * @str: The string representation of the alias
 *
 * Return: Always returns 0 on success, 1 on error
 */
int set_alias(info_t *info, char *str)
{
    char *equal_sign;

    equal_sign = strchr(str, '=');
    if (!equal_sign)
        return 1;
    if (!*(++equal_sign))
        return unset_alias(info, str);

    unset_alias(info, str);
    return add_node_end(&(info->alias), str, 0) == NULL;
}

/**
 * print_alias - function to print an alias string
 * @nodes: The alias node to print
 *
 * Return: Always returns 0 on success, 1 on error
 */
int print_alias(list_t *nodes)
{
    char *equal_sign = NULL, *alias = NULL;

    if (nodes)
    {
        equal_sign = strchr(nodes->str, '=');
        for (alias = nodes->str; alias <= equal_sign; alias++)
            putchar(*alias);
        putchar('\'');
        puts(equal_sign + 1);
        puts("'\n");
        return 0;
    }
    return 1;
}

/**
 * my_alias - function that mimics the alias builtin (man alias)
 * @info: Structure containing potential arguments, used to maintain a constant function prototype.
 *
 * Return: Always returns 0
 */
int my_alias(info_t *info)
{
    int i = 0;
    char *equal_sign = NULL;
    list_t *nodes = NULL;

    if (info->argc == 1)
    {
        nodes = info->alias;
        while (nodes)
        {
            print_alias(nodes);
            nodes = nodes->next;
        }
        return 0;
    }
    for (i = 1; info->argv[i]; i++)
    {
        equal_sign = strchr(info->argv[i], '=');
        if (equal_sign)
            set_alias(info, info->argv[i]);
        else
            print_alias(node_starting_with(info->alias, info->argv[i], '='));
    }
    return 0;
}

