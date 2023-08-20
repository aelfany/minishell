/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelfany <abelfany@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 14:24:21 by abelfany          #+#    #+#             */
/*   Updated: 2023/08/20 03:16:02 by abelfany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	not_2(char c)
{
	if (c == '|' || c == '<' || c == '>')
		return (0);
	return (1);
}

int	check_command(t_creat *list)
{
	while (list && ft_strcmp(list-> token, "PIP"))
	{
		if (!ft_strcmp(list -> token, "CMD"))
			return (1);
		list = list -> next;
	}
	return (0);
}

void	ft_lstadd_back(t_creat **lst, t_creat *new)
{
	t_creat	*tmp;

	if (!lst)
		return ;
	if (!new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	tmp = *lst;
	while (tmp -> next != NULL)
		tmp = tmp -> next;
	tmp -> next = new;
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	if (s1 == NULL || s2 == NULL)
		return (0);
	while (s1[i] || s2[i])
	{
		if (s1[i] > s2[i] || s1[i] < s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (0);
}

char	*ft_strdup(const char *s1)
{
	int		a;
	int		res;
	char	*cpy;

	a = 0;
	res = strlen(s1) + 1;
	cpy = (char *)malloc(res * sizeof(char));
	if (!cpy)
		return (0);
	while (s1[a])
	{
		cpy[a] = s1[a];
		a++;
	}
	cpy[a] = '\0';
	return (cpy);
}
