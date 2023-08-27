/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelfany <abelfany@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 14:20:31 by abelfany          #+#    #+#             */
/*   Updated: 2023/08/27 05:45:35 by abelfany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
	if (c == '\'' || c == '"' || c == '<'
		|| c == '>' || c == '$')
		return (0);
	return (1);
}

int	check_error(char *str, int x)
{
	int	a;
	int	sv;
	int	flag;

	a = x;
	flag = 0;
	sv = 0;
	while (str[a] && str[a] == '|')
	{
		sv++;
		a++;
	}
	if (!str[a])
		return (1);
	while (x--)
		if (!is_wts(str[x]) && not_2(str[x]))
			flag = 1;
	a--;
	while (str[++a])
		if (!is_wts(str[a]) && not_2(str[a]))
		{
			flag++;
			break ;
		}
	if (sv > 1 || flag < 2)
		return (1);
	return (0);
}

void	read_string_utils(t_creat **res, char *str, int *y, t_env *envr)
{
	int	x;

	x = *y;
	if (not(str[x]))
		take_string(str, &x, res, envr);
	if (!counter_quots(str) && (str[x] == '\'' || str[x] == '"'))
		who_first(str, &x, res, envr);
	if (str[x] == '>' && str[x + 1] != '>')
		x += check_rederction(str + x, res, '>', envr);
	if (str[x] == '<' && str[x + 1] != '<')
		x += check_rederction(str + x, res, '<', envr);
	if (str[x] == '<' && str[x + 1] == '<')
		check_heredoc(str, &x, res);
	if (str[x] == '>' && str[x + 1] == '>')
		rederction_apn(str, &x, res, envr);
	if (str[x] == '$')
		check_expand_new(str, &x, res, envr);
	if (str[x] == '|' && check_error(str, x))
		insert(res, ft_strdup("|"), "PIP", 1);
	else if (str[x] == '|')
		insert(res, ft_strdup("|"), "PIP", 0);
	(*y) = x;
}

t_creat		*read_string(t_creat **list, char *str, t_env *envr)
{
	t_creat *res;
	int		count;
	int		x;

	count = 0;
	x = skip_w_space(str);
	res = NULL;
	while (str[x])
	{
		if (counter_quots(str))
		{
			error_handler("QT");
			count = 1;
			break ;
		}
		read_string_utils(&res, str, &x, envr);
		if (synatx_er(res))
			return ((*list) = NULL, free_list(&res), NULL);
		if (str[x] == '\0')
			break ;
		if (not_red(str[x]) || is_wts(str[x]) || str[x] == '$')
			x++;
	}
	(*list) = res;
	return (new_list(res));
}
