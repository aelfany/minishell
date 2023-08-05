#include "minishell.h"

void	ft_exec(t_vars *var)
{
	int	fd;
	int id;

	fd = -1;
	fd = ft_check_redirections(var);
	// char **st = malloc(8 * 3);
	// st[0] = "/usr/bin/grep";
	// st[1] = "a";
	// st[2] = NULL;
	id = fork();
	if (id == 0)
	{
		dup2(fd, 0);
		close(fd);
	}
	if (id == 0)
	{
		execve(var->cmd, var->cmd_options, var->envr);
		perror(var->cmd);
		exit(1);
	}
	waitpid(-1, NULL, 0);
}