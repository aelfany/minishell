#include "minishell.h"

// to check for required built ins
int	check_built_ins(t_vars *var)
{
	int	i;
	int	d;

	i = 0;
	d = 0;
	if (var->cmd_options[0][0] == '<')
		d = 2; 
	while(i < 7)
	{
		if(strcmp(var->cmd_options[d], var->builtins[i]) == 0)
			return (i);
		i++;
	}
	return(-1);
}

// checks for redirections
int	ft_check_redirections(t_vars *var)
{
	int	fd;

	fd = -1;
	// int	m;

	// i = 0;
	// m = 0;
	if (var->cmd_options[0][0] == '<')
		fd = open(var->cmd_options[1], O_RDONLY);
	return (fd);
}