#include "../minishell.h"

static void	ft_remove_first(t_env **envr, t_env **ptr, t_env **prev)
{
	if ((*envr)->next != NULL)
		*envr = (*envr)->next;
	if ((*ptr)->free_flag == 0)
		free((*ptr)->opt);
	if ((*ptr)->free_flag == 2 || (*ptr)->free_flag == 0)
		free((*ptr)->envr);
	(*prev) = (*ptr);
	(*ptr) = (*ptr)->next;
	free((*prev));
}

static void	ft_remove_others(t_env **ptr, t_env **prev)
{
	(*prev)->next = (*prev)->next->next;
	(*ptr)->next = NULL;
	if ((*ptr)->free_flag == 0)
		free((*ptr)->opt);
	if ((*ptr)->free_flag == 2 || (*ptr)->free_flag == 0)
		free((*ptr)->envr);
	free((*ptr));
}

void	unset(t_env **envr, t_vars *var)
{
	t_env	*ptr;
	t_env	*prev;
	int		i;
	int		d;

	ptr = *envr;
	prev = *envr;
	i = 1;
	d = 1;
	if (ft_count_vars(var->cmd_options) == 1)
		return ;
	while (var->cmd_options[d])
	{
		if (ft_export_parser(var->cmd_options[d], 1) == -1)
		{
			d++;
			continue ;
		}
		while (ptr)
		{
			if (ft_strcmp(ptr->opt, "PWD") == 0 && ft_strcmp(var->cmd_options[d], "PWD") == 0)
			{
				ptr->hidden_flag= 1;
			}
			else if (ft_strcmp(var->cmd_options[d], ptr->opt) == 0)
				{
					if (i == 1) //if its the first node on the list
					{
						ft_remove_first(envr, &ptr, &prev);
						break;
					}
					while(i > 2) //if its in the middle 
					{
						prev = prev->next;
						i--;
					}
					ft_remove_others(&ptr, &prev);
					break;
				}
				ptr = ptr->next;
				i++;
		}
		ptr = *envr;
		prev = *envr;
		d++;
		i = 1;
	}
}