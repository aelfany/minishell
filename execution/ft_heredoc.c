/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelfany <abelfany@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 18:02:49 by anchaouk          #+#    #+#             */
/*   Updated: 2023/08/26 23:59:22 by abelfany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//(*var)->hrd_line = ft_strjoin((*var)->hrd_line, "\n");
//expand right under this line

void	here_doc_handler(int a)
{
	if (a == 2)
	{
		printf("\n");
		exit(1);
	}
	else if (a == 3)
		return ;
	return ;
}

static void	heredoc_output(t_vars **var, t_env *envr, int flag)
{
	char	*res;
	int		i;

	res = NULL;
	i = 0;
	(*var)->hrd_line = ft_strjoin((*var)->hrd_line, "\n");
	while ((*var)->hrd_line[i])
	{
		if ((*var)->hrd_line[i] == '$' && flag == 0)
			res = ft_strjoin(res, take_expand_heredoc((*var)->hrd_line, &i, envr));
		else if ((*var)->hrd_line[i] && (*var)->hrd_line[i] != '$' && flag == 0)
		{
			res = ft_charjoin(res, (*var)->hrd_line[i]);
			i++;
		}
		else
		{
			res = ft_charjoin(res, (*var)->hrd_line[i]);
			i++;
		}
	}
	ft_putstr_fd(res, (*var)->hd_pipe[1]);
	free(res);
}

static void	here_doc_helper(t_vars **var, char *delim, t_env *envr, int flag)
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
			heredoc_output(var, envr, flag);
		free((*var)->hrd_line);
	}
}

void	here_doc(t_creat **res, t_vars **var, t_env *envr, int id)
{
	int	flag;
	int	status;

	while ((*res))
	{
		if (ft_check_hrd((*res)->token) == 0)
		{
			flag = ft_exp_check((*res)->token);
			close((*var)->hd_pipe[1]);
			close((*var)->hd_pipe[0]);
			ft_systemcall_protect(pipe((*var)->hd_pipe));
			signal(SIGINT, handler_ignore);
			signal(SIGQUIT, handler_ignore);
			id = fork();
			ft_systemcall_protect(id);
			if (id == 0)
			{
				signal(SIGINT, here_doc_handler);
				signal(SIGQUIT, here_doc_handler);
				close((*var)->hd_pipe[0]);
				here_doc_helper(&(*var), (*res)->cmd, envr, flag);
			}
			waitpid(id, &status, 0);
			signals();
			g_exitstatus = WIFEXITED(status);
		}
		(*res) = (*res)->next;
	}
}

void	ft_open_heredocs(t_creat **res, t_vars **var, t_env *envr)
{
	t_vars	*ptr_var;
	t_creat	*ptr;

	ptr_var = (*var);
	ptr = (*res);
	ptr_var->og_in = dup(0);
	ptr_var->og_out = dup(1);
	while (ptr)
	{
		if (ft_check_hrd(ptr->token) == 0)
		{
			here_doc(&ptr, &ptr_var, envr, 1);
			close(ptr_var->hd_pipe[1]);
			if (ptr_var->hd_pipe[0] != -1)
				dup2(ptr_var->hd_pipe[0], 0);
			close(ptr_var->hd_pipe[0]);
			break ;
		}
		ptr = ptr->next;
	}
	return ;
}
