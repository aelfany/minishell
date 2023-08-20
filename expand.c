/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelfany <abelfany@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 22:34:23 by abelfany          #+#    #+#             */
/*   Updated: 2023/08/20 00:52:17 by abelfany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_expand_cases(char *str, int x)
{
	if (str[x] == '$' && str[x + 1] == '*')
		return (1);
	return (0);
}

void	error_hh(char *str)
{
	ft_putstr_fd(str, 2);
	exit(0);
}

int	is_yes(char c)
{
	if (c == '|' || c == '<' || c == '>' || ft_isspace(c))
		return (1);
	return (0);
}

char	*check_expand_rd(char *str, int *x, t_env *env)
{
	int		a;
	char	*word;
	char	*join;

	a = x[0];
	word = 0;
	while (str[a])
	{
		if (is_yes(str[a]))
			break ;
		if (str[a] == '"' || str[a] == '\'')
		{
			join = quots_expand(str, &a, env);
			word = ft_strjoin(word, join);
		}
		if (str[a] == '$')
		{
			join = take_expand_word(str, &a, env);
			word = ft_strjoin(word, join);
		}
	}
	(*x) = a;
	return (word);
}

void	check_expand(char *str, int *x, t_creat **res, t_env *env)
{
	int		a;
	char	*word;
	char	*join;

	a = x[0];
	word = NULL;
	while (str[a])
	{
		if (is_yes(str[a]))
			break ;
		if (str[a] == '"' || str[a] == '\'')
		{
			join = quots_expand(str, &a, env);
			word = ft_strjoin(word, join);
		}
		if (str[a] == '$')
		{
			join = take_expand_word(str, &a, env);
			word = ft_strjoin(word, join);
		}
	}
	(*x) = a;
	insert(res, word, "CMD", 0);
}
