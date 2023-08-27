/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anchaouk <anchaouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 17:31:17 by anchaouk          #+#    #+#             */
/*   Updated: 2023/08/23 22:25:57 by anchaouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_deploy_commands(t_vars *var, t_creat *ptr, t_env *envr)
{
	if (var->i == 0)
		ft_close_first(var->pipe, ptr, var, envr);
	else if (var->i == (var->cmd_count -1))
		ft_close_last(var->pipe, ptr, var, envr);
	else if (var->i < (var->cmd_count - 1))
		ft_close_pipe(var->pipe, ptr, var, envr);
}

int	ft_wait(t_vars *var)
{
	int	status;

	ft_close_all_p(var, 0);
	while (1)
	{
		if (waitpid(-1, &status, 0) == -1)
			break ;
	}
	free(var->pipe);
	free(var->pid);
	exitstatus_handler(status);
	printf("exitstatus pipe = %d\n", g_exitstatus);
	return (0);
}
// return 1 if heredoc is last
// return 0 if rd in is last

static	int	ft_check_input(t_creat **res)
{
	int	flag;

	flag = 0;
	while ((*res) && ft_strcmp((*res)->token, "PIP") != 0)
	{
		if (ft_strcmp((*res)->token, "HRD") == 0
			|| ft_strcmp((*res)->token, "HRD_SQ") == 0
			|| ft_strcmp((*res)->token, "HRD_DQ") == 0)
			flag = 1;
		else if (ft_strcmp((*res)->token, "RDIN") == 0)
			flag = 0;
		(*res) = (*res)->next;
	}
	return (flag);
}

void	ft_input_fix(t_vars **var, t_creat *res)
{
	t_vars	*ptr;

	ptr = (*var);
	ptr->i = 0;
	while (res && ptr->i < ptr->cmd_count)
	{
		if (ft_check_input(&res) == 1 && ptr->pipe_in[ptr->i] != -1)
		{
			close(ptr->pipe_in[ptr->i]);
			ptr->pipe_in[ptr->i] = ptr->pipe_hrd[ptr->i];
		}
		if (res && ft_strcmp(res->token, "PIP") == 0)
		{
			ptr->i++;
			res = res->next;
			continue ;
		}
		else if (!res)
			break ;
	}
	ptr->i = 0;
}

int	pipes_exec(t_creat *res, t_vars *var, t_env *envr)
{
	t_creat	*ptr;

	ptr = res;
	ft_init_p_vars(var, res);
	ft_heredoc_p(res, var);
	rd_init(res, var);
	while (var->i < var->cmd_count && ptr)
	{
		var->pid[var->i] = fork();
		ft_systemcall_protect(var->pid[var->i]);
		if (var->pid[var->i] == 0 && ft_strcmp(ptr->token, "CMD") == 0)
			ft_deploy_commands(var, ptr, envr);
		else if (var->pid[var->i] == 0)
			ft_close_all_p(var, 1);
		if (ft_strcmp(ptr->token, "PIP") == 0)
			var->i++;
		ptr = ptr->next;
	}
	return (ft_wait(var));
}
