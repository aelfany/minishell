/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelfany <abelfany@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 14:20:31 by abelfany          #+#    #+#             */
/*   Updated: 2023/08/20 04:02:09 by abelfany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_last(char *str, int *flag, char c)
{
	int	f;
	int	a;

	a = 1;
	f = 0;
	while (str[a])
	{
		if (str[a] == c)
		{
			f = 1;
			break ;
		}
		a++;
	}
	(*flag) = f;
	return (a);
}

int	counter_quots(char *str)
{
	int	b;
	int	flag;

	b = 0;
	while (str[b])
	{
		if (str[b] == '"' || str[b] == '\'')
		{
			b += find_last(str + b, &flag, str[b]);
			if (flag == 0)
				return (1);
		}
		b++;
	}
	return (0);
}

int	not_red(char c)
{
	if (c == '\'' || c == '"' || c == '|' || c == '<'
		|| c == '>' || c == '$')
		return (0);
	return (1);
}

void	read_string_utils(t_creat **res, char *str, int *y, t_env *envr)
{
	int	x;

	x = y[0];
	if (not(str[x]))
		take_string(str, &x, res, envr);
	if (!counter_quots(str) && (str[x] == '\'' || str[x] == '"'))
		who_first(str, &x, res, envr);
	if (str[x] == '<' && str[x + 1] == '<')
		check_heredoc(str, &x, res);
	if (str[x] == '>' && str[x + 1] == '>')
		rederction_apn(str, &x, res, envr);
	if (str[x] == '>' && str[x + 1] != '>')
		x += check_rederction(str + x, res, '>', envr);
	if (str[x] == '<' && str[x + 1] != '<')
		x += check_rederction(str + x, res, '<', envr);
	if (str[x] == '|')
	{
		insert(res, "|", "PIP", 0);
		x++;
	}
	(*y) = x;
}

t_creat	*read_string(char *str, t_env *envr)
{
	t_creat	*res;
	int		count;
	int		x;

	count = 0;
	res = NULL;
	x = skip_w_space(str);
	while (str[x])
	{
		if (counter_quots(str))
		{
			error_handler("QT");
			count = 1;
			break ;
		}
		read_string_utils(&res, str, &x, envr);
		if (str[x] == '$')
			check_expand(str, &x, &res, envr);
		if (!str[x])
			break ;
		if (not_red(str[x]) || ft_isspace(str[x]) || str[x] == '$')
			x++;
	}
	if(count == 0)
		return (NULL);
	return (new_list(res));
}
