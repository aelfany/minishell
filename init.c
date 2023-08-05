#include "minishell.h"

// initalizes the needed variables in the struct
void	init_vars(t_vars *var, char **env)
{
	var->exitcode = 0;
	var->pipe_count = 0;
	var->redirections_bool = -1;
	var->builtins = malloc(sizeof(char *) * 8);
	var->builtins[0] = "cd"; 
	var->builtins[1] = "echo";
	var->builtins[2] = "pwd";
	var->builtins[3] = "export";
	var->builtins[4] = "unset";
	var->builtins[5] = "env";
	var->builtins[6] = "exit";
	var->builtins[7] = NULL;
	var->envr = env;
}