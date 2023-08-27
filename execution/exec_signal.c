/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_signal.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anchaouk <anchaouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 12:17:58 by anchaouk          #+#    #+#             */
/*   Updated: 2023/08/24 18:10:28 by anchaouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handler_child(int a)
{	
	if (a == 3)
		printf("Quit: 3\n");
	else if (a != 3)
		printf("\n");
	return ;
}

void	handler_ignore(int a)
{
	if (a == 3)
		return ;
	else if (a != 3)
		return ;
	return ;
}

void	exec_signals(t_creat *res)
{
	if (ft_strcmp(res->cmd, "./minishell") == 0)
	{
		signal(SIGINT, handler_ignore);
		signal(SIGQUIT, handler_ignore);
	}
	else
	{
		signal(SIGINT, handler_child);
		signal(SIGQUIT, handler_child);
	}
}

void	exitstatus_handler(int status)
{
	if (WIFEXITED(status) != 0)
		g_exitstatus = WEXITSTATUS(status);
	else if (WIFSIGNALED(status) != 0)
	{
		g_exitstatus = WTERMSIG(status);
		if (g_exitstatus == 2)
			g_exitstatus = 130;
		if (g_exitstatus == 3)
			g_exitstatus = 131;
	}
}
