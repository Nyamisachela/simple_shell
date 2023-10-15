#include "Shell.h"
/**
*print_env - prints the environment variables
*/
void print_env(void)
{
	char **env;

	env = environ;
	while (env)
	{
		printf("%s\n", *env);
		env++;
	}
}
