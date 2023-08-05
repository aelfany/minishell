#include "minishell.h"

void	ft_execone(int	*end, t_vars *var)
{
	// printf("%s\n", var->op2[0]);
	// printf("one : %d\n", end[1]);
	dup2(end[1], STDOUT_FILENO);
	close(end[0]);
	close(end[1]);
	execve(var->op[0], var->op, var->envr);
	perror(var->cmd_options[0]);
}

void	ft_execpipe(int *end1, int *end0, t_vars *var)
{
	dup2(end0[0], STDIN_FILENO);
	dup2(end1[1], STDOUT_FILENO);
	close(end0[1]);
	close(end0[0]);
	close(end1[1]);
	close(end1[0]);
	execve(var->op2[0], var->op2, var->envr);
	perror(var->op2[0]);
}

void	ft_exectwo(int *end, t_vars *var)
{
	// printf("two : %s\n",var->cmd_options[4]);
	// var->test[0] = var->cmd_options[4];
	// var->cmd = command_finder(var->cmd_options[4], getenv("PATH"));
	dup2(end[0], STDIN_FILENO);
	dup2(1, STDOUT_FILENO);
	close(end[0]);
	close(end[1]);
	// write(1, "its out\n", 8);
	execve(var->op1[0], var->op1, var->envr);
	perror(var->op1[0]);
}
