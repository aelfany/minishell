#include "minishell.h"

int	ft_count_vars(char **env)
{
	int	i;

	i = 1;
	while(env[i])
		i++;
	return (i);
}

int	append_count(char *env)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while(env[i] != '=' && env[i])
		{
			if (env[i] == '+')
				count++;
			i++;
		}
	if (count > 1)
		return (-1);
	i = 0;
	while(env[i] != '=' && env[i])
		{
			if (env[i] == '+' && env[i + 1] != '=')
				return(-1);
			i++;
		}
	return (0);
}

int	ft_export_parser(char *env, int n)
{
	int	i;
	int	flag;

	i = 0;
	flag = 1;
	if (append_count(env) == -1 && n == 0)
	{
		flag = -1;
	}
	else if ((env[i] >= 65 && env[i] <= 90) || (env[i] >= 97 && env[i] <= 122))
		flag = 0;
	else if (env[i] == '_')
		flag = 0;
	else
		flag = -1;
	if (flag == -1 && n == 0)
	{
		ft_putstr_fd("minishell: export: `", 2);
		ft_putstr_fd(env, 2);
		ft_putstr_fd("\': not a valid identifier\n", 2);
	}
	else if (flag == -1 && n == 1)
	{
		ft_putstr_fd("minishell: unset: `", 2);
		ft_putstr_fd(env, 2);
		ft_putstr_fd("\': not a valid identifier\n", 2);
	}
	return (flag);
}