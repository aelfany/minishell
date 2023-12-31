/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anchaouk <anchaouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 17:55:04 by anchaouk          #+#    #+#             */
/*   Updated: 2023/08/23 16:35:03 by anchaouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_loop(char **opt)
{
	int	i;

	i = 0;
	while(opt[i])
	{
		free(opt[i]);
		i++;
	}
}

void	ft_free_struct(t_env *env, t_creat *res)
{
	t_creat	*ptr;
	t_env	*ptr_env;

	ptr = res;
	ptr_env = env;
	if (ptr)
	{
		while (ptr)
		{
			free(ptr);
			ptr = ptr->next;
		}
	}
	if (ptr_env)
	{
		while (ptr_env)
		{
			free(ptr);
			ptr_env = ptr_env->next;
		}
	}
}