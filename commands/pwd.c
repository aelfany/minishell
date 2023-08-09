#include "../minishell.h" 

int	pwd(t_env *envr)
{
	t_env	*ptr;
	int		flag;

	ptr = envr;
	flag = 0;
	while(ptr)
	{
		if (ft_strcmp(ptr->opt, "PWD") == 0)
		{
			printf("%s\n", ptr->envr);
			flag = 1;
			break;
		}
		ptr = ptr->next;
	}
	if (flag == 0)
		printf(".\n");
	return (0);
}