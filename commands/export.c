#include "../minishell.h"

static void	print_env(t_env *envr)
{
	t_env	*ptr;

	ptr = envr;
	while(ptr->next)
	{
		printf("declare -x %s=%s\n", ptr->opt, ptr->quoted_env);
		ptr = ptr->next;
	}
}

int	calc_size(char *str, char delim)
{
	int	i;

	i = 0;
	while(str[i])
	{
		if (str[i] == delim)
			return (i);
		i++;
	}
	return(i);
}

void	ft_export(t_env *envr, t_vars *var)
{
	t_env	*ptr;
	int		i;
	int		flag;
	char	**opt = ft_split(var->line_read, ' ');

	ptr = envr;
	i = 0;
	flag = 1;
	while(opt[1] && opt[1][i++])
		if(opt[1][i] == '=' && ft_strlen(opt[1]) > 2)
			flag = 0;
	if (!opt[1])
		flag = 2;
	if (flag == 0)
	{
		while(ptr->next)
			ptr = ptr->next;
		ptr->next = malloc(sizeof(t_env) * 1);
		ptr = ptr->next;
		ptr->envr = opt[1];
		ptr->opt = malloc(1 * calc_size(ptr->envr, '='));
		ft_fillup(ptr);
		ptr->next = NULL; 
	}
	else if (flag == 2)
		print_env(envr);
}
