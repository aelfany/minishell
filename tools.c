/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anchaouk <anchaouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 19:09:55 by anchaouk          #+#    #+#             */
/*   Updated: 2023/08/24 21:47:40 by anchaouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isnum(char *str)
{
	int	i;
	
	i = 0;
	while(str[i])
	{
		if (str[i] >= 48 && str[i] <= 57)
			i++;
		else
			return (-1);
	}
	return (0);
}

void	ft_putstr_fd(char *str, int fd)
{
	int	i;

	i = 0;
	if (str == NULL)
		return ;
	while (str[i])
	{
		write(fd, &str[i], 1);
		i++;
	}
}

int	ft_strlen_delim(char *str, char delim)
{
	int	i;

	i = 0;
	while (str[i] != delim && str[i])
		i++;
	return (i);
}

int	calc_size(char *str, char delim)
{
	int	i;
	int	d;

	i = 0;
	d = 0;
	while (str[i])
	{
		if (str[i] == '+')
			d = 1;
		if (str[i] == delim)
			return (i);
		i++;
	}
	i = i - d;
	return (i);
}

int	ft_lenstrs(char **strs)
{
	int	x;

	x = 0;
	while (strs[x])
		x++;
	return (x);
}

int	ft_free(char **strs)
{
	int	x;

	x = 0;
	while (strs[x])
		free(strs[x++]);
	free(strs);
	return (0);
}