/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_fun.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelfany <abelfany@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 14:19:37 by abelfany          #+#    #+#             */
/*   Updated: 2023/08/27 06:10:52 by abelfany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*insert_expand_word(t_creat **res, char **word)
{
	char	**spl;
	char	*join;
	int		b;

	b = 0;
	join = NULL;
	spl = split_word(*word, "\t ");
	join = ft_strjoin(join, spl[b++]);
	insert(res, join, "CMD", 0);
	while (spl[b + 1])
		insert(res, spl[b++], "CMD", 0);
	return (free(*word), *word = spl[b], *word);
}

char	*expand(t_env *env, int count, char *word)
{
	int	a;

	a = -1;
	while (env)
	{
		if (!ft_strcmp(env -> name, word))
		{
			free(word);
			word = NULL;
			if (count % 2)
			{
				while (env -> value[++a])
					word = _remallc(word, env -> value[a]);
			}
			if(word == NULL)
			{
				word = malloc(2);
				return (word[0] = 0, word);
			}
			return (word);
		}
		env = env -> next;
	}
	word = malloc(2);
	return (word[0] = 0, word);
}

char	*expand_red(t_env *env, int count, char *word, t_creat **res)
{
	int	a;
	int	flag;

	a = -1;
	flag = 0;
	while (env)
	{
		if (wc(env -> value) == 1 &&!ft_strcmp(env -> name, word))
		{
			flag = 1;
			if (count % 2)
			{
				word = NULL;
				while (env -> value[++a])
					word = _remallc(word, env -> value[a]);
			}
			return (word);
		}
		env = env -> next;
	}
	if (flag == 0)
		insert(res, word, word, 1);
	if (env == NULL && count % 2)
		word[0] = 0;
	return (word);
}
