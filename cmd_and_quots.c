/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_and_quots.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelfany <abelfany@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 23:56:05 by abelfany          #+#    #+#             */
/*   Updated: 2023/08/20 03:32:45 by abelfany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*quts(char *str, int *x, t_env *env)
{
	t_str	u;

	u.flag = '\'';
	if (str[u.b] == '"')
		u.flag = '"';
	u.word = malloc(2);
	u.word[0] = 0;
	u.b = x[0] + 1;
	while (str[u.b] != u.flag && str[u.b] && not_2(str[u.b]))
	{
		if (str[u.b] == '$' && u.flag == '"')
		{
			if (str[u.b] == '"' || str[u.b] == '\'')
				u.b++;
			u.word = ft_strjoin(u.word, take_expand_word(str, &u.b, env));
			if (str[u.b] == u.flag)
				break ;
		}
		else
			u.word = _remallc(u.word, str[u.b]);
		if (str[u.b] && str[u.b] && str[u.b] != '$')
			u.b++;
	}
	(*x) = u.b;
	return (u.word);
}

char	*_remallc(char *str, char c)
{
	char	*save;
	int		a;

	a = -1;
	save = malloc(strlen(str) + 1);
	while (str[++a])
		save[a] = str[a];
	save[a] = 0;
	free(str);
	str = malloc((strlen(str) + 2) * sizeof(char));
	str[strlen(save)] = c;
	str[strlen(save) + 1] = 0;
	a = -1;
	while (save[++a])
		str[a] = save[a];
	free(save);
	return (str);
}

int	not_3(char c)
{
	if (c == '|' || c == '<' || c == '>')
		return (0);
	return (1);
}

void	who_first(char *str, int *x, t_creat **res, t_env *env)
{
	t_str	u;

	u.b = x[0];
	u.word = malloc(2);
	u.word[0] = 0;
	while (str[u.b] && !ft_isspace(str[u.b]))
	{
		if (str[u.b] == '$')
			u.word = ft_strjoin(u.word, take_expand_word(str, &u.b, env));
		if (str[u.b] == '"' || str[u.b] == '\'')
			u.word = ft_strjoin(u.word, quts(str, &u.b, env));
		else if (str[u.b] != '$' && not_2(str[u.b]) && str[u.b])
			u.word = _remallc(u.word, str[u.b]);
		if (!str[u.b] || !not_2(str[u.b]) || ft_isspace(str[u.b]))
			break ;
		u.b++;
	}
	(*x) = u.b;
	insert(res, u.word, "CMD", 0);
}

void	take_string(char *str, int *x, t_creat **res, t_env *env)
{
	t_str	u;

	u.word = malloc(2);
	u.word[0] = 0;
	u.b = x[0];
	while (str[u.b] && !ft_isspace(str[u.b]) && not_3(str[u.b]))
	{
		if ((str[u.b] != '"' && str[u.b] != '\'') && str[u.b] != '$')
			u.word = _remallc(u.word, str[u.b]);
		if (str[u.b] == '$')
			u.word = ft_strjoin(u.word, take_expand_word(str, &u.b, env));
		if ((str[u.b] == '"' || str[u.b] == '\''))
			u.word = ft_strjoin(u.word, quts(str, &u.b, env));
		if (!str[u.b])
			break ;
		u.b++;
	}
	(*x) = u.b;
	insert(res, u.word, "CMD", 0);
}
