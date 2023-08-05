#include "minishell.h"

int	check_pipes(t_vars *var)
{
	int	i;

	i = 0;
	while(var->line_read[i])
	{
		if (var->line_read[i] == '|')
			return (1);
		i++;
	}
	return (0);
}

void	pipe_calc(t_vars *var)
{
	int	i;

	i = 0;
	var->pipe_count = 0;
	while(var->line_read[i])
	{
		if(var->line_read[i] == '|')
			var->pipe_count++;
		i++;
	}
	var->cmd_count = var->pipe_count + 1;
}

void	ft_pipe(t_vars *var)
{
	int	i;

	i = 0;
	// printf("pipe : %d\n", var->pipe_count);
	while (i < var->pipe_count)
	{
		pipe(var->pipe[i]);
		// printf("%d -- %d\n", var->pipe[i][0], var->pipe[i][1]);
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

int	pipes_exec(t_vars *var)
{
	// ft_pipe_heredoc(ac, av, env);
	pipe_calc(var);
	var->i = 0;
	var->pid = malloc(sizeof(int) * (var->cmd_count));
	var->pipe = malloc(sizeof(int *) * (var->pipe_count));
	var->test = malloc(sizeof(char *) * 3);
	var->test[3] = NULL;
	var->test[0] = "/bin/ls ";
	var->test[1] = "/usr/bin/grep mini ";
	var->test[2] = "/usr/bin/wc ";
	var->op = ft_split(var->test[0], ' ');
	var->op1 = ft_split(var->test[1], ' ');
	var->op2 = ft_split(var->test[2], ' ');
	ft_pipe(var);		
	while (var->i < var->cmd_count)
	{
		var->pid[var->i] = fork();
		if (var->pid[var->i] == 0 && var->i == 0)
		{
			printf("in one %d\n", var->i);
			ft_close_first(var->pipe, var);
		}
		else if (var->pid[var->i] == 0 && var->i == (var->cmd_count -1))
		{
			printf("in last %d\n", var->i);
			ft_close_last(var->pipe, var);
		}
		else if (var->pid[var->i] == 0 && var->i < (var->cmd_count - 1))
		{
			printf("in middle %d\n", var->i);
			ft_close_pipe(var->pipe, var);
		}
		var->i++;
	}
	ft_wait(var);
	return (0);
}