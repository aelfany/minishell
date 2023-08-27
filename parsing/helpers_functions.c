/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelfany <abelfany@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 01:22:40 by abelfany          #+#    #+#             */
/*   Updated: 2023/08/27 14:30:23 by abelfany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	synatx_er(t_creat *res)
{
	while (res)
	{
		if (res -> ex == 1)
		{
			error_handler(res -> token);
			return (1);
		}
		res = res -> next;
	}
	return (0);
}

int	syntax_pipes(char *str)
{
	int	a;

	a = 1;
	while (str[a] && str[a] != '|')
	{
		if (!is_wts(str[a]))
			return (1);
		a++;
	}
	return (0);
}

int	ft_cmp(char *s1, char *s2)
{
	int	a;

	a = 0;
	while (s1[a] && s1[a] == s2[a])
		a++;
	return (s1[a] - s2[a]);
}

void	error_hh(char *str)
{
	ft_putstr_fd(str, 2);
	exit(0);
}
