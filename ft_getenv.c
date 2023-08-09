/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anchaouk <anchaouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 16:44:41 by anchaouk          #+#    #+#             */
/*   Updated: 2023/08/04 15:40:11 by anchaouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_getenv(t_env *envr, char *var)
{
	t_env	*ptr;

	ptr = envr;
	while(ptr)
	{
		if (ft_strcmp(ptr->opt, var) == 0)
			return (ptr->envr);
		ptr = ptr->next;
	}
	return (0);
}