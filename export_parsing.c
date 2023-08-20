/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_parsing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anchaouk <anchaouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 12:39:22 by anchaouk          #+#    #+#             */
/*   Updated: 2023/08/17 14:35:15 by anchaouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//counts for the + signs parsing 

int	append_count(char *env)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (env[i] != '=' && env[i])
	{
		if (env[i] == '+')
			count++;
		i++;
	}
	if (count > 1)
		return (-1);
	i = 0;
	while (env[i] != '=' && env[i])
	{
		if (env[i] == '+' && env[i + 1] != '=')
			return (-1);
		i++;
	}
	return (0);
}

static int	ft_helper(char *env, int n, int i)
{
	int	flag;

	flag = 0;
	while (env[i])
	{
		if (env[i] == ' ' || env[i] == '\t')
			return (-1);
		i++;
	}
	if (append_count(env) == -1 && n == 0)
		flag = -1;
	else if ((env[0] >= 65 && env[i] <= 90) || (env[0] >= 97 && env[0] <= 122))
		flag = 0;
	else if (env[0] == '_')
		flag = 0;
	else
		flag = -1;
	return (flag);
}

int	ft_count_vars(char **opt, t_env *envr)
{
	int	i;

	i = 1;
	while (opt[i])
		i++;
	if (i == 1)
	{
		print_env(envr);
		g_exitstatus = 0;
	}
	return (i);
}

int	ft_export_parser(char *env, int n)
{
	int	i;
	int	flag;

	i = 0;
	flag = ft_helper(env, n, i);
	if (flag == -1 && n == 0)
	{
		ft_putstr_fd("minishell: export: `", 2);
		ft_putstr_fd(env, 2);
		ft_putstr_fd("\': not a valid identifier\n", 2);
		g_exitstatus = 1;
	}
	else if (flag == -1 && n == 1)
	{
		ft_putstr_fd("minishell: unset: `", 2);
		ft_putstr_fd(env, 2);
		ft_putstr_fd("\': not a valid identifier\n", 2);
		g_exitstatus = 1;
	}
	return (flag);
}
