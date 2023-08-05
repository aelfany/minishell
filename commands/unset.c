#include "../minishell.h" 

void	unset(t_env *envr, t_vars *var)
{
	t_env	*ptr;
	t_env	*prev;
	int		i;

	ptr = envr;
	prev = envr;
	i = 0;
	while(ptr)
	{
		if (ft_strcmp(var->cmd_options[1], ptr->opt) == 0)
			{
				free(ptr->opt);
				// ptr->envr = "G";
				i--;
				while(i > 0)
				{
					prev = prev->next;
					i--;
				}
				prev->next = prev->next->next;
				ptr->next = NULL;
				// printf(" wwww %s\n", prev->envr);
				// if (prev->next->next == NULL)
				// 	prev->next = NULL;
				// else if (prev->next->next != NULL)
				// 	prev->next = prev->next->next;
				break;
			}
			i++;
			ptr = ptr->next;
	}
}