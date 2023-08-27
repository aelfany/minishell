/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_and_quots.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelfany <abelfany@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 23:56:05 by abelfany          #+#    #+#             */
/*   Updated: 2023/08/27 06:28:34 by abelfany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*quts(char *str, int *x, t_env *env)
{
	t_str	u;

	u.flag = '\'';
	if (str[*x] == '"')
		u.flag = '"';
	u.word = NULL;
	u.b = *x + 1;
	while (str[u.b] != u.flag && str[u.b])
	{
		if (str[u.b] == '$' && u.flag == '"')
		{
			u.word = ft_strjoin_free(u.word, expand_word(str, &u.b, env), 1, 1);
			if (str[u.b] == u.flag)
				break ;
		}
		if (str[u.b] && str[u.b] == '$' && u.flag == '\'')
			u.word = _remallc(u.word, str[u.b++]);
		if (str[u.b] == u.flag)
			break ;
		if (str[u.b] && str[u.b] != '$')
			u.word = _remallc(u.word, str[u.b]);
		if (str[u.b] && str[u.b] != '$')
			u.b++;
	}
	(*x) = u.b;
	return (u.word);
}

char	*_remallc(char *str, char c)
{
	char	*save;
	int		a;
	int		b;

	if (!str)
	{
		str = malloc(1);
		str[0] = 0;
	}
	b = ft_strlen(str);
	save = malloc(b + 2);
	if (!save)
		return (NULL);
	save[b] = c;
	save[b + 1] = 0;
	a = -1;
	while (str[++a])
		save[a] = str[a];
	free(str);
	return (save);
}

int	not_4(char c)
{
	if (c == '<' || c == '>')
		return (0);
	return (1);
}

void	who_first(char *str, int *x, t_creat **res, t_env *env)
{
	t_str	u;

	u.b = x[0];
	u.word = NULL;
	while (str[u.b] && !is_wts(str[u.b]))
	{
		if (str[u.b] == '$')
			u.word = ft_strjoin_free(u.word, expand_word(str, &u.b, env), 1, 1);
		if (str[u.b] == '"' || str[u.b] == '\'')
			u.word = ft_strjoin_free(u.word, quts(str, &u.b, env), 1, 1);
		else if (str[u.b] != '$' && not_4(str[u.b]) && str[u.b])
			u.word = _remallc(u.word, str[u.b]);
		if (str[u.b] == '|' || !str[u.b] 
			|| !not_2(str[u.b]) || is_wts(str[u.b]))
			break ;
		u.b++;
	}
	(*x) = u.b;
	insert(res, u.word, "CMD", 0);
}

void	take_string(char *str, int *x, t_creat **res, t_env *env)
{
	t_str	u;

	u.word = NULL;
	u.b = x[0];
	while (str[u.b] && !is_wts(str[u.b]) && not_3(str[u.b]))
	{
		if ((str[u.b] != '"' && str[u.b] != '\'') && str[u.b] != '$')
			u.word = _remallc(u.word, str[u.b]);
		if (str[u.b] == '$')
			u.word = ft_strjoin_free(u.word, expand_word(str, &u.b, env), 1, 1);
		if ((str[u.b] == '"' || str[u.b] == '\''))
			u.word = ft_strjoin_free(u.word, quts(str, &u.b, env), 1, 1);
		if (!str[u.b])
			break ;
		u.b++;
	}
	(*x) = u.b;
	insert(res, u.word, "CMD", 0);
}
