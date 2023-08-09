#include "../minishell.h" 

void	ft_env(t_env *envr)
{
	int		i;
	t_env	*ptr;

	i = 0;
	ptr = envr;
	if (envr->opt == NULL)
		return;
	while(ptr)
	{
		if (ptr->hidden_flag == 0 && ptr->opt != NULL && ptr->envr != NULL)
			printf("%s=", ptr->opt);
		else if (ptr->hidden_flag == 0 && ptr->opt != NULL && ptr->envr == NULL)
			printf("%s=\n", ptr->opt);
		if (ptr->hidden_flag == 0 && ptr->envr != NULL)
			printf("%s\n",ptr->envr);
		ptr = ptr->next;
	}
}