/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anchaouk <anchaouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 19:01:52 by anchaouk          #+#    #+#             */
/*   Updated: 2023/08/18 22:26:37 by anchaouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static	int	ft_isnum(int c)
{
    if (c >= 48 && c <= 57)
		return (1);
	return (0);
}

static	void	ft_exit_error(char *str, int flag)
{
	if (flag == 0)
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		g_exitstatus = 255;
	}
	else if (flag == 1)
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd("too many arguments\n", 2);
		g_exitstatus = 1;
	}
}

//checks first arg if numeric and has more args
// its too many args and dosent quit

//if its none numeric its args required and exits

static int	exit_parser(char **opt, int flag, int i)
{
	unsigned long long	exitcode;

	exitcode = 0;
	if (opt[1] && flag == 0)
	{
		exitcode = ft_atoi(opt[1]);
		while (ft_isnum(opt[1][i]) == 1 && opt[1][i])
			i++;
		if (opt[1][i] != '\0' || exitcode < 0)
		{
			ft_exit_error(opt[1], 0);
			return (-1);
		}
	}
	else if (flag == 1)
	{
		while(opt[i]) 
			i++;
		if (i > 2)
		{
			ft_exit_error(opt[1], 1);
			return (-1);
		}
	}
	return (0);
}

static	void	free_me(t_env *env, t_creat *res, t_vars *var)
{
	t_env	*ptr;
	t_env	*prev;

	ptr = env;
	(void)res;
	while (ptr)
	{
		if (ptr->free_name == 0)
			free(ptr->name);
		if (ptr->free_value == 0)
			free(ptr->value);
		prev = ptr;
		ptr = ptr->next;
		free(prev);
	}
	free(var->builtins);
}

int	ft_exit(long long exitcode, t_env *env, t_creat *res, t_vars *var)
{
	if (exit_parser(res->opt, 0, 0) == -1)
		exitcode = g_exitstatus;
	else if (exit_parser(res->opt, 1, 0) == -1)
		return (1);
	else if (res->opt[1])
		exitcode = ft_atoi(res->opt[1]);
	else
		exitcode = 0;
	free_me(env, res, var);
	printf("exit\n");
	exit(exitcode);
}
