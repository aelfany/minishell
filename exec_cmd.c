#include "minishell.h"

static void	ft_error_exec(t_vars *var)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(var->cmd, 2);
	ft_putstr_fd(": No such file or directory\n", 2);
}

void	ft_exec(t_vars *var, int id)
{
	int	fd;
	// int id;

	fd = -1;
	fd = ft_check_redirections(var);
	// id = fork();
	// if (id == 0)
	// {
	// 	dup2(fd, 0);
	// 	close(fd);
	// }
	if (id == 0)
	{
		execve(var->cmd, var->cmd_options, var->envr);
		ft_error_exec(var);
		exit(1);
	}
	// waitpid(id, NULL, 0);
}