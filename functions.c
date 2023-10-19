#include "shell.h"

/**
 * exit_shell - function to exit the shell
 * @info: Structure containing potential arguments, used to maintain a consistent function prototype.
 *
 * Return: Exits the shell with a given exit status (0) if info->argv[0] != "exit".
 */
int exit_shell(info_t *info)
{
    int exit_code;

    if (info->argv[1]) // If there is an exit argument
    {
        exit_code = str_to_int(info->argv[1]);
        if (exit_code == -1)
        {
            info->status = 2;
            print_error(info, "Illegal number: ");
            eputs(info->argv[1]);
            eputchar('\n');
            return 1;
        }
        info->err_number = str_to_int(info->argv[1]);
        return -2;
    }
    info->err_number = -1;
    return -2;
}

/**
 * change_directory - function to change the current directory of the process
 * @info: Structure containing potential arguments, used to maintain a consistent function prototype.
 *
 * Return: Always returns 0
 */
int change_directory(info_t *info)
{
    char *s, *dir, buffer[1024];
    int chdir_result;

    s = getcwd(buffer, 1024);
    if (!s)
        puts("TODO: >>getcwd failure emsg here<<\n");
    if (!info->argv[1])
    {
        dir = getenv_variable(info, "HOME=");
        if (!dir)
            chdir_result = chdir((dir = getenv_variable(info, "PWD=")) ? dir : "/");
        else
            chdir_result = chdir(dir);
    }
    else if (strcmp(info->argv[1], "-") == 0)
    {
        if (!getenv_variable(info, "OLDPWD="))
        {
            puts(s);
            putchar('\n');
            return 1;
        }
        puts(getenv_variable(info, "OLDPWD="));
        chdir_result = chdir((dir = getenv_variable(info, "OLDPWD=")) ? dir : "/");
    }
    else
        chdir_result = chdir(info->argv[1]);
    if (chdir_result == -1)
    {
        print_error(info, "can't cd to ");
        eputs(info->argv[1]);
        eputchar('\n');
    }
    else
    {
        setenv_variable(info, "OLDPWD", getenv_variable(info, "PWD="));
        setenv_variable(info, "PWD", getcwd(buffer, 1024));
    }
    return 0;
}

/**
 * display_help - function to provide help information
 * @info: the structure containing potential arguments, used to maintain a consistent function prototype.
 *
 * Return: Always returns 0
 */
int display_help(info_t *info)
{
    char **arg_array;

    arg_array = info->argv;
    puts("Help function called. Function not yet implemented.\n");
    if (0)
        puts(*arg_array); // Temporary, unused workaround
    return 0;
}

