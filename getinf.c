#include "shell.h"

/**
 * clear_info - Initializes the info_t structure, resetting its fields.
 * @info: Pointer to the info_t structure to be cleared.
 */
void clear_info(info_t *info)
{
    info->arg = NULL;
    info->argv = NULL;
    info->paths = NULL;
    info->argc = 0;
}

/**
 * set_info - Initializes the info_t structure with provided arguments.
 * @info: Pointer to the info_t structure.
 * @argv: Argument vector.
 */
void set_info(info_t *info, char **argv)
{
    int i = 0;

    info->file_name = argv[0];
    if (info->arg)
    {
        info->argv = strtow(info->arg, " \t");
        if (!info->argv)
        {
            info->argv = malloc(sizeof(char *) * 2);
            if (info->argv)
            {
                info->argv[0] = strdup(info->arg);
                info->argv[1] = NULL;
            }
        }
        for (i = 0; info->argv && info->argv[i]; i++)
            ;
        info->argc = i;

        replace_alias(info);
        replace_vars(info);
    }
}

/**
 * free_info - Frees the fields of the info_t structure.
 * @info: Pointer to the info_t structure.
 * @all: True if all fields should be freed.
 */
void free_info(info_t *info, int all)
{
    ffree(info->argv);
    info->argv = NULL;
    info->paths = NULL;
    if (all)
    {
        if (!info->cmd_buffer)
            free(info->arg);
        if (info->envv)
            free_list(&(info->envv));
        if (info->_history)
            free_list(&(info->_history));
        if (info->alias)
            free_list(&(info->alias));
        ffree(info->environs);
        info->environs = NULL;
        bfree((void **)info->cmd_buffer);
        if (info->to_readfd > 2)
            close(info->to_readfd);
        putchar(BUF_FLUSH);
    }
}

