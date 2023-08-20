/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelfany <abelfany@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 18:02:49 by anchaouk          #+#    #+#             */
/*   Updated: 2023/08/20 00:04:48 by abelfany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	here_doc_helper(t_vars **var, char *delim)
{
	while (1)
	{
		(*var)->hrd_line = readline("> ");
		if (ft_strcmp((*var)->hrd_line, delim) == 0)
			exit(0);
		else
		{
			(*var)->hrd_line = ft_strjoin((*var)->hrd_line, "\n");
			ft_putstr_fd((*var)->hrd_line, (*var)->hd_pipe[1]);
		}
		free((*var)->hrd_line);
	}
}

void	here_doc(t_creat **res, t_vars **var)
{
	int	id;

	id = 1;
	while ((*res))
	{
		if (ft_strcmp((*res)->token, "HRD") == 0)
		{
			close((*var)->hd_pipe[1]);
			close((*var)->hd_pipe[0]);
			pipe((*var)->hd_pipe);
			id = fork();
			if (id == 0)
			{
				close((*var)->hd_pipe[0]);
				here_doc_helper(&(*var), (*res)->cmd);
			}
			while (1)
			{
				if (waitpid(-1, NULL, 0) == -1)
					break ;
			}
		}
		(*res) = (*res)->next;
	}
}

void	ft_open_heredocs(t_creat **res, t_vars **var)
{
	t_vars	*ptr_var;
	t_creat	*ptr;
	int		flag;

	ptr_var = (*var);
	ptr = (*res);
	flag = 0;
	while (ptr)
	{
		if (ft_strcmp(ptr->token, "HRD") == 0)
			flag = 1;
		ptr = ptr->next;
	}
	ptr = (*res);
	if (flag == 1)
	{
		here_doc(&ptr, &ptr_var);
		close(ptr_var->hd_pipe[1]);
		if (ptr_var->hd_pipe[0] != -1 && flag == 1)
			dup2(ptr_var->hd_pipe[0], 0);
		close(ptr_var->hd_pipe[0]);
	}
	else
		return ;
}
