#include "minishell.h"

char	*my_get_env(t_env *envr, char *id) // obviously my version of get_env return the value of the name given else sends null
{
	int	i;
	t_env	*ptr;

	i = 0;
	ptr = envr;
	while(ptr)
	{
		if (ft_strcmp(ptr->opt, id) == 0)
			return (ptr->envr);
		ptr = ptr->next;
	}
	return (NULL);
}

void	ft_fillup_unset(t_env **envr) //if env gets unsetted env -i
{
	t_env	*ptr;

	ptr = *envr;
	ptr->free_flag = 1;
	ptr->hidden_flag = 1;
	ptr->opt = "PATH";
	ptr->envr = "/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:.";
	ptr->next = malloc(sizeof(t_env) * 1);
	ptr = ptr->next;
	ptr->opt = "PWD";
	ptr->envr = getcwd(NULL, 0);
	ptr->free_flag = 2;
	ptr->hidden_flag = 0;
	ptr->next = malloc(sizeof(t_env) * 1);
	ptr = ptr->next;
	ptr->opt = "SHLVL";
	ptr->envr = "1";
	ptr->free_flag = 1;
	ptr->hidden_flag = 0;
	ptr->next = malloc(sizeof(t_env) * 1);
	ptr = ptr->next;
	ptr->opt = "_";
	ptr->envr = "/usr/bin/env";
	ptr->free_flag = 1;
	ptr->hidden_flag = 0;
	ptr->next = NULL;
}

void	ft_fillup_envr(t_env *str, char *env) //fills up the value 
{
	int	i;
	int	d;

	d = 0;
	i = 0;
	(void)str;
	while(env[i] != '=')
		i++;
	i++;
	while(env[i])
	{
		str->envr[d] = env[i];
		i++;
		d++;
	}
	str->envr[d] = '\0';
}

void	ft_fillup(t_env *str, char *env) //fills up the id name
{
	int	i;
	int	d;

	i = 0;
	d = 0;
	while(env[i] != '=' && env[i])
	{
		if (env[i] == '+')
		{
			i++;
			continue;
		}
		str->opt[d] = env[i];
		i++;
		d++;
	}
	str->opt[d] = '\0';
}

void	fill_env(t_env **envr, char **env) // fills up env list
{
	t_env	*ptr;
	int		i;
	int		d; 
	ptr = *envr;
	i = 0;
	d = 0;
	if (env[0] == NULL) //if the env are deleted 
	{
		printf("WARNING: terminal is not fully functional\n");
		ft_fillup_unset(envr);
		return ;
	}
	while(env[i])
	{
		d = calc_size(env[i], '=');
		ptr->opt = malloc(1 * d + 1);
		ft_fillup(ptr, env[i]); //fills up name 
		if (ft_strcmp(ptr->opt, "OLDPWD") == 0) //if equals oldpwd skip it ps : it gets created until cd is used
			{
				i++;
				free(ptr->opt);
				continue ;
			}
		ptr->envr = malloc(1 * (ft_strlen(env[i]) - d) + 1);
		if (!ptr->opt || !ptr->envr)
			{
				perror("malloc\n");
				exit(-1);
			}
		ft_fillup_envr(ptr, env[i]); //filling up  the value of name
		ptr->next = malloc(sizeof(t_env) * 1);
		ptr->free_flag = 0;
		ptr->hidden_flag = 0;
		if (env[i + 1])//checks if env is still going 
			ptr = ptr->next;
		else
			free(ptr->next);
		i++;
	}
	ptr->next = NULL;
	}
