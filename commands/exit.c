#include "../minishell.h" 

int	ft_exit(int	exitcode, t_env *env, t_vars *var)
{
	int		i;
	t_env	*ptr;
	t_env	*prev;

	i = 0;
	ptr = env;
	ptr = env;
	if (var->cmd_options[1])
		exitcode = ft_atoi(var->cmd_options[1]);
	free(var->builtins);
	while(ptr)
	{
		if (ptr->free_flag == 0)
			free(ptr->opt);
		if (ptr->free_flag == 2 || ptr->free_flag == 0)
			free(ptr->envr);
		prev = ptr;
		ptr = ptr->next;
		free(prev);
	}
	
	printf("exit\n");
	exit(exitcode);
}