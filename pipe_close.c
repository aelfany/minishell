#include "minishell.h"

void	ft_close_first(int end[][2],t_vars *var)
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
	printf("first %d\n", var->i);
	ft_execone(end[var->i], var);
}

void	ft_close_last(int end[][2], t_vars *var)
{
	int	d;

	d = 0;
	// printf("pipes = %d\n", var->pipe_count);
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
	// printf("%d\n", var->i-1);
	// printf("sec %d\n", var->i);
	ft_exectwo(end[var->i - 1],var);
	puts("iiin\n");
}

void	ft_close_pipe(int end[][2], t_vars *var)
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
	ft_execpipe(var->pipe[var->i], var->pipe[var->i - 1], var);
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
