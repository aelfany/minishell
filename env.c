#include "minishell.h"

void	ft_fillup(t_env *str)
{
	int	i;
	int	d;

	i = 0;
	d = 0;
	while(str->envr[i] != '=')
	{
		str->opt[i] = str->envr[i];
		i++;
	}
	i++;
	str->quoted_env = malloc(1 * (ft_strlen(str->envr) - i ) + 2);
	if (!str->quoted_env)
		return;
	str->quoted_env[d] = '"';
	d++;
	while(str->envr[i])
	{
		str->quoted_env[d] = str->envr[i];
		d++;
		i++;
	}
	str->quoted_env[d] = '"';
}

void	fill_env(t_env *envr, char **env)
{
	t_env	*ptr;
	int		i;

	ptr = envr;
	i = 0;
	while(env[i])
	{
		ptr->envr = env[i];
		ptr->opt = malloc(1 * calc_size(ptr->envr, '='));
		ft_fillup(ptr);
		ptr->next = malloc(sizeof(t_env) * 1);
		if (env[i + 1])
			ptr = ptr->next;
		else
			free(ptr->next);
		i++;
	}
	ptr->next = NULL;
	}
