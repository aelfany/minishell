/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anchaouk <anchaouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 13:01:12 by anchaouk          #+#    #+#             */
/*   Updated: 2023/08/24 16:28:26 by anchaouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	add_1pwd(t_env *ptr)
{
	ptr->next = malloc(sizeof(t_env) * 1);
	ft_malloc_protect(ptr->next);
	ptr = ptr->next;
	ptr->free_name = 1;
	ptr->free_value = 0;
	ptr->hidden_flag = 1;
	ptr->name = "1PWD";
	ptr->value = getcwd(NULL, 0);
	ptr->next = NULL;
}

// obviously my version of get_env return
// the value of the name given else sends null

char	*my_get_env(t_env *envr, char *id)
{
	int		i;
	t_env	*ptr;

	i = 0;
	ptr = envr;
	while (ptr)
	{
		if (ft_strcmp(ptr->name, id) == 0)
			return (ptr->value);
		ptr = ptr->next;
	}
	return (NULL);
}

//if the env are deleted 

int	check_env_unavailable(t_env **envr, char *env)
{
	if (env == NULL)
	{
		printf("WARNING: terminal is not fully functional\n");
		ft_fillup_unset(envr);
		return (1);
	}
	return (0);
}

t_env	*ft_fillup_unset_help(t_env **envr)
{
	t_env	*ptr;

	ptr = *envr;
	ptr->name = "PATH";
	ptr->value = "/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:.";
	ptr->free_name = 1;
	ptr->free_value = 1;
	ptr->hidden_flag = 1;
	ptr->next = malloc(sizeof(t_env) * 1);
	ft_malloc_protect(ptr->next);
	ptr = ptr->next;
	ptr->name = "PWD";
	ptr->value = getcwd(NULL, 0);
	ptr->free_name = 1;
	ptr->free_value = 0;
	ptr->hidden_flag = 0;
	ptr->next = malloc(sizeof(t_env) * 1);
	ft_malloc_protect(ptr->next);
	ptr = ptr->next;
	ptr->name = "1PWD";
	ptr->value = getcwd(NULL, 0);
	ptr->free_name = 1;
	ptr->free_value = 0;
	return (ptr);
}

//if env gets unsetted env -i

void	ft_fillup_unset(t_env **envr)
{
	t_env	*ptr;

	ptr = NULL;
	ptr = ft_fillup_unset_help(envr);
	ptr->hidden_flag = 1;
	ptr->next = malloc(sizeof(t_env) * 1);
	ft_malloc_protect(ptr->next);
	ptr = ptr->next;
	ptr->name = "SHLVL";
	ptr->value = "1";
	ptr->free_name = 1; 
	ptr->free_value = 1; 
	ptr->hidden_flag = 0;
	ptr->next = malloc(sizeof(t_env) * 1);
	ft_malloc_protect(ptr->next);
	ptr = ptr->next;
	ptr->name = "_";
	ptr->value = "/usr/bin/env";
	ptr->free_name = 1;
	ptr->free_value = 1;
	ptr->hidden_flag = 0;
	ptr->next = NULL;
}
