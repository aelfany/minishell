#include "minishell.h"

int	check_pipes(t_creat *res)
{
	t_creat	*ptr;

	ptr = res;
	while (ptr)
	{
		if (ft_strcmp(ptr->token, "PIP") == 0)
			return (1);
		ptr = ptr->next;
	}
	return (0);
}

void	pipe_calc(t_creat *res, t_vars *var)
{
	t_creat	*ptr;

	ptr = res;
	var->pipe_count = 0;
	while(ptr)
	{
		if(ft_strcmp(ptr->token, "PIP") == 0)
			var->pipe_count++;
		ptr = ptr->next;
	}
	var->cmd_count = var->pipe_count + 1;
}

void	ft_pipe(t_vars *var)
{
	int	i;

	i = 0;
	while (i < var->pipe_count)
	{
		pipe(var->pipe[i]);
		i++;
	}
}

int	ft_wait(t_vars *var)
{
	ft_close_all(var);
	while (1)
		if (waitpid(-1, NULL, 0) == -1)
			break ;
	free(var->pipe);
	free(var->pid);
	return (0);
}

int	pipes_exec(t_creat *res, t_vars *var)
{
	t_creat	*ptr;

	ptr = res;
	pipe_calc(res, var);
	ft_pipe(var);
	var->i = 0;
	while (var->i < var->cmd_count && ptr)
	{
		var->pid[var->i] = fork();
		if (var->pid[var->i] == 0 && var->i == 0)
			ft_close_first(var->pipe, ptr->opt, var);
		else if (var->pid[var->i] == 0 && var->i == (var->cmd_count -1))
			ft_close_last(var->pipe, ptr->opt, var);
		else if (var->pid[var->i] == 0 && var->i < (var->cmd_count - 1))
			ft_close_pipe(var->pipe, ptr->opt, var);
		var->i++;
		ptr = ptr->next;
	}
	ft_wait(var);
	return (0);
}