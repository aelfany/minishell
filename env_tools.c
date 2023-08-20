/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anchaouk <anchaouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 13:01:12 by anchaouk          #+#    #+#             */
/*   Updated: 2023/08/16 18:56:37 by anchaouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_1pwd(t_env *ptr)
{
	ptr->next = malloc(sizeof(t_env) * 1);
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
