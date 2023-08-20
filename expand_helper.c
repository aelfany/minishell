/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelfany <abelfany@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 07:57:17 by abelfany          #+#    #+#             */
/*   Updated: 2023/08/20 00:55:25 by abelfany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	if_expand(char c)
{
	if (c == '-' || c == '*' || ft_isdigit(c) || ft_isspace(c))
		return (1);
	return (0);
}

char	*quots_expand(char *str, int *x, t_env *env)
{
	int		b;
	char	*word;
	char	*join;

	b = x[0];
	word = malloc(2);
	word[0] = 0;
	while (str[b] && !ft_isspace(str[b]))
	{
		if (str[b] == '"' || str[b] == '\'')
		{
			join = quts(str, &b, env);
			word = ft_strjoin(word, join);
		}
		else
			word = _remallc(word, str[b++]);
		if (!str[b] || !not_2(str[b]) || str[b] == '$' || ft_isspace(str[b]))
			break ;
		b++;
	}
	(*x) = b;
	return (word);
}

char	*expand(t_env *env, int count, char *word)
{
	int	a;

	a = -1;
	while (env)
	{
		if (!ft_strcmp(env -> name, word))
		{
			if (count % 2)
			{
				word = malloc(2);
				word[0] = 0;
				while (env -> value[++a])
					word = _remallc(word, env -> value[a]);
			}
			return (word);
		}
		env = env -> next;
	}
	if (env == NULL && count % 2)
		word[0] = 0;
	return (word);
}

char	*take_expand_word(char *str, int *x, t_env *env)
{
	int		b;
	char	*word;
	int		count;

	word = malloc(2);
	word[0] = 0;
	count = 0;
	b = x[0] - 1;
	while (str[++b] == '$')
		count++;
	while (str[b] && not(str[b]))
		word = _remallc(word, str[b++]);
	if (count % 2 && word[0] == 0)
		return ((*x) = b, _remallc(word, '$'));
	word = expand(env, count, word);
	(*x) = b;
	return (word);
}
