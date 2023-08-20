#include "minishell.h"

void	ft_close_first(int end[][2], char **opt, t_vars *var)
{
	int	d;

	d = 0;
	while (d < var->pipe_count)
	{
		if (d == 0)
			close(end[d][0]);
		else
		{
			close(end[d][0]);
			close(end[d][1]);
			
		}
	d++;
	}
	ft_execone(end[var->i], opt, var);
}

void	ft_close_last(int end[][2], char **opt, t_vars *var)
{
	int	d;

	d = 0;
	while (d < var->pipe_count)
	{
		if (d == var->pipe_count -1)
			close(end[d][1]);
		else
		{
			close(end[d][1]);
			close(end[d][0]);
		}
		d++;
	}
	ft_exectwo(end[var->i - 1], opt, var);
}

void	ft_close_pipe(int end[][2], char **opt, t_vars *var)
{
	int	d;

	d = 0;
	while (d < var->pipe_count)
	{
		if (d == (var->i - 1))
			close(end[d][1]);
		else if (d == var->i)
			close(end[d][1]);
		else
		{
			close(end[d][0]);
			close(end[d][1]);
		}
		d++;
	}
	ft_execpipe(var->pipe[var->i], var->pipe[var->i - 1], var, opt);
}

void	ft_close_all(t_vars *var)
{
	int	d;

	d = 0;
	while (d < var->pipe_count)
	{
		close(var->pipe[d][0]);
		close(var->pipe[d][1]);
		d++;
	}
}
