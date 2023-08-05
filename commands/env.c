#include "../minishell.h" 

void	ft_env(t_env *envr)
{
	int		i;
	t_env	*ptr;

	i = 0;
	ptr = envr;
	while(ptr)
	{
		if(ptr->envr[0])
			printf("%s\n", ptr->envr);
		ptr = ptr->next;
	}
}