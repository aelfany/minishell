/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_hrd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anchaouk <anchaouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 17:57:39 by anchaouk          #+#    #+#             */
/*   Updated: 2023/08/23 22:07:59 by anchaouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//(*var)->hrd_line = ft_strjoin((*var)->hrd_line, "\n");
//expand right under this line

// SIGINT CTRL - C
// SIGQUIT CTRL - BACKSLASH

static void	here_doc_helper(t_vars **var, char *delim)
{
	while (1)
	{
		(*var)->hrd_line = readline("> ");
		if (ft_strcmp((*var)->hrd_line, delim) == 0)
		{
			free((*var)->hrd_line);
			exit(0);
		}
		else
		{
			(*var)->hrd_line = ft_strjoin((*var)->hrd_line, "\n");
			ft_putstr_fd((*var)->hrd_line, (*var)->hd_pipe[1]);
		}
		free((*var)->hrd_line);
	}
}

static void	here_doc(t_creat **res, t_vars **var)
{
	int	id;

	id = 1;
	if ((*var)->pipe_hrd[(*var)->i] != -2)
	{
		close((*var)->hd_pipe[0]);
		close((*var)->hd_pipe[1]);
	}
	else
	{
		(*var)->hd_pipe[0] = -2;
		close((*var)->hd_pipe[1]);
	}
	pipe((*var)->hd_pipe);
	id = fork();
	ft_systemcall_protect(id);
	hrd_signal_reset(id);
	if (id == 0)
	{
		close((*var)->hd_pipe[0]);
		here_doc_helper(&(*var), (*res)->cmd);
	}
	waitpid(id, NULL, 0);
}

static void	ft_open_heredocs_p(t_creat **res, t_vars **var)
{
	(*var)->p_hrd = -2; 
	while ((*res) && ft_strcmp((*res)->token, "PIP") != 0)
	{
		if (ft_strcmp((*res)->token, "HRD") == 0)
		{
			close((*var)->p_hrd);
			here_doc(res, var);
			close((*var)->hd_pipe[1]);
			(*var)->p_hrd = (*var)->hd_pipe[0]; 
		}
		(*res) = (*res)->next;
	}
	(*var)->pipe_hrd[(*var)->i] = (*var)->p_hrd;
	return ;
}

void	ft_heredoc_p(t_creat *res, t_vars *var)
{
	t_creat	*ptr;

	ptr = res;
	var->p_hrd = -2;
	var->i = 0;
	while (ptr && var->i < var->cmd_count)
	{
		ft_open_heredocs_p(&ptr, &var);
		if (ptr && ft_strcmp(ptr->token, "PIP") == 0)
		{
			ptr = ptr->next;
			var->i++;
			var->p_hrd = -2;
			continue ;
		}
		else if (!ptr)
			break ;
	}
	var->i = 0;
	ft_pipe(var);
}
