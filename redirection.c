/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelfany <abelfany@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 14:19:37 by abelfany          #+#    #+#             */
/*   Updated: 2023/08/20 04:02:49 by abelfany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	skip_space(char *str)
{
	int	a;

	a = 0;
	while (str[a] == '\t' || str[a] == '\n' || str[a] == '\v'
		|| str[a] == '\f' || str[a] == '\r' || str[a] == ' ')
		a++;
	return (a);
}

int	add_red_token(t_creat **res, char *word, char c, int x)
{
	if (c == '<')
		insert(res, word, "RDIN", 0);
	else if (c == '>')
		insert(res, word, "RDOUT", 0);
	return (x);
}

int	check_rederction(char *str, t_creat **res, char c, t_env *env)
{
	t_str	u;

	u.word = malloc(2);
	u.word[0] = 0;
	u.b = 1;
	u.b += skip_space(str + u.b);
	while (str[u.b] && !ft_isspace(str[u.b]) && not_2(str[u.b]))
	{
		if (str[u.b] == '$')
			u.word = ft_strjoin(u.word, take_expand_word(str, &u.b, env));
		while (not_2(str[u.b]) && str[u.b] && (str[u.b] != '"'
				&& str[u.b] != '\'') && !ft_isspace(str[u.b]))
			u.word = _remallc(u.word, str[u.b++]);
		if (str[u.b] && !ft_isspace(str[u.b]) && not_2(str[u.b]))
			u.word = ft_strjoin(u.word, quts(str, &u.b, env));
		if (str[u.b] && !ft_isspace(str[u.b]) && not_2(str[u.b]))
			u.b++;
	}
	if(!u.word[0])
		error_handler("newline");
	return (add_red_token(res, u.word, c, u.b), u.b);
}

void	rederction_apn(char *str, int *x, t_creat **res, t_env *env)
{
	t_str	u;

	u.word = malloc(2);
	u.word[0] = 0;
	u.b = x[0] + 2;
	u.b += skip_space(str + u.b);
	while (str[u.b] && !ft_isspace(str[u.b]) && not_2(str[u.b]))
	{
		if (str[u.b] == '$')
			u.word = ft_strjoin(u.word, take_expand_word(str, &u.b, env));
		while (not_2(str[u.b]) && str[u.b] && (str[u.b] != '"'
				&& str[u.b] != '\'') && !ft_isspace(str[u.b]))
			u.word = _remallc(u.word, str[u.b++]);
		if (str[u.b] && !ft_isspace(str[u.b]) && not_2(str[u.b]))
			u.word = ft_strjoin(u.word, quts(str, &u.b, env));
		if (str[u.b] && !ft_isspace(str[u.b]) && not_2(str[u.b]))
			u.b++;
	}
	(*x) = u.b;
	if(!u.word[0])
		error_handler("newline");
	insert(res, u.word, "RD_AP", 0);
}
