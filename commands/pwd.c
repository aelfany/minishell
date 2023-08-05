#include "../minishell.h" 

int	pwd()
{
	char d[100];
	char *s = getcwd(d, sizeof(d));
	printf("%s\n", s);
	return (0);
}