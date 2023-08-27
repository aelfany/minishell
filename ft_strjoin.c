/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anchaouk <anchaouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 20:12:13 by anchaouk          #+#    #+#             */
/*   Updated: 2023/08/24 17:53:37 by anchaouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

char	*ft_charjoin(char *str, char c)
{
	size_t	i;
	char	*alloc;

	if (!c)
		return (0);
	if (!str)
	{
		alloc = (char *)malloc(sizeof(char) * 2);
		alloc[0] = c;
		alloc[1] = '\0';
		return (alloc);
	}
	i = 0;
	alloc = (char *)malloc(sizeof(char) * (ft_strlen(str) + 2));
	ft_malloc_protect(alloc);
	while (str[i])
	{
		alloc[i] = str[i];
		i++;
	}
	alloc[i] = c;
	alloc[i + 1] = '\0';
	free(str); 
	return (alloc);
}

char	*ft_strjoin(char *s1, char *s2)
{
	size_t	i;
	size_t	lenres;
	char	*alloc;

	if (!s2)
		return (s1);
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

char	*ft_strjoin_free(char *s1, char *s2, int f, int s)
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
	if (f == 1)
		free(s1);
	if (s == 1)
		free(s2);
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
