#include "../minishell.h" 

int	ft_exit(int	exitcode, t_env *env, t_vars *var)
{
	int	i;

	i = 0;
	if (var->cmd_options[1])
		exitcode = ft_atoi(var->cmd_options[1]);
	free(var->builtins);
	while(env)
	{
		free(env->opt);
		free(env->quoted_env);
		env = env->next;
	}
	printf("exit\n");
	exit(exitcode);
}