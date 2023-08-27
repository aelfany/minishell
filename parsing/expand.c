/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelfany <abelfany@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 22:34:23 by abelfany          #+#    #+#             */
/*   Updated: 2023/08/27 06:28:34 by abelfany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_expand_cases(char *str, int x)
{
	if (str[x] == '$' && str[x + 1] == '*')
		return (1);
	return (0);
}

int	is_yes(char c)
{
	if (c == '|' || c == '<' || c == '>' || is_wts(c))
		return (1);
	return (0);
}

int	wc(char *str)
{
	int	x;
	int	count;

	x = 0;
	count = 0;
	if (!str)
		return (0);
	if (!is_wts(str[0]))
		count++;
	while (str[x])
	{
		if ((is_wts(str[x]) && !is_wts(str[x + 1])) && str[x + 1] != '\0')
			count++;
		x++;
	}
	return (count);
}

void	check_expand_new(char *str, int *x, t_creat **res, t_env *env)
{
	int		b;
	int		a;
	int		flag;
	char	*join;

	join = NULL;
	a = *x;
	b = 0;
	flag = 0;
	while (str[a])
	{
		if (str[a] == '$')
			join = ft_strjoin_free(join, expand_word(str, &a, env), 1, 1);
		if (wc(join) > 1)
			join = insert_expand_word(res, &join);
		if (!str[a] || is_yes(str[a]))
			break ;
		if (str[a] != '$')
			a++;
	}
	(*x) = a;
	if (join[0] != 0)
		insert(res, join, "CMD", 0);
	else
		free(join);
}
