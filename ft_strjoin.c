/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anchaouk <anchaouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 20:12:13 by anchaouk          #+#    #+#             */
/*   Updated: 2023/07/16 16:22:06 by anchaouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while(str[i])
		i++;
	return (i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	size_t	lenres;
	char	*alloc;

	if (!s2)
		return (0);
	i = 0;
	lenres = ft_strlen(s1);
	alloc = (char *)malloc(sizeof(char) * (lenres + ft_strlen(s2) + 1));
	if (!alloc)
		return (0);
	while (i < lenres && s1[i] != '\0')
	{
		alloc[i] = s1[i];
		i++;
	}
	i = 0;
	while (i <= lenres && s2[i] != '\0')
	{
			alloc[lenres] = s2[i];
			lenres++;
			i++;
	}
	alloc[lenres] = '\0';
	return (alloc);
}

char	*ft_strjoin_space(char const *s1, char const *s2)
{
	size_t	i;
	size_t	lenres;
	char	*alloc;

	if (!s2)
		return (0);
	i = 0;
	lenres = ft_strlen(s1);
	alloc = (char *)malloc(sizeof(char) * (lenres + ft_strlen(s2) + 1));
	if (!alloc)
		return (0);
	while (i < lenres && s1[i] != '\0')
	{
		alloc[i] = s1[i];
		i++;
	}
	i = 0;
	while (i <= lenres && s2[i] != '\0')
	{
			alloc[lenres] = s2[i];
			lenres++;
			i++;
	}
	alloc[lenres] = '\0';
	return (alloc);
}