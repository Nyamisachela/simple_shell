#include "Shell.h"
/**
*print_env - prints the environment variables
*/
void print_env(void)
{
	char **env;

	env = environ;
	while (*env)
	{
		write(1, *env, _strlen(*env));
		write(1, "\n", 1);
		env++;
	}
}
