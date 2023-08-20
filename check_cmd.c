#include "minishell.h"

// to check for required built ins
int	check_built_ins(t_creat *res, t_vars *var)
{
	int	i;
	int	d;

	i = 0;
	d = 0;
	while(i < 7)
	{
		if(ft_strcmp(res->cmd, var->builtins[i]) == 0)
			return (i);
		i++;
	}
	return(-1);
}
