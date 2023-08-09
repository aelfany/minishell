	#include "../minishell.h"

void	print_env(t_env *envr)
{
	t_env	*ptr;

	ptr = envr;
	while(ptr)
	{
		if (ptr->envr ==  NULL)
			printf("declare -x %s=" "\n", ptr->opt);
		else if (ptr->hidden_flag == 0)
			printf("declare -x %s=\"%s\"\n", ptr->opt, ptr->envr);
		ptr = ptr->next;
	}
}

int	ft_check_append(char *str) //checks if it needs to be appended if true returns 1
{
	int	i;

	i = 0;
	while(str[i])
	{
		if (str[i] == '+' && str[i + 1] == '=')
			return (1);
		i++;
	}
	return (0);
}

int	ft_change_env(t_env *env_struct, char *str)
{
	int		i;
	int		d;
	char	*append;
	char	*result;

	i = ft_strlen_delim(str, '=');
	d = 0;
	append = NULL;
	result = NULL;
	i++;
	if (ft_check_append(str) == 1 || env_struct->envr == NULL)
	{
		append = malloc(1 * (ft_strlen(str) - i) + 1);
		while(str[i])
		{
			append[d] = str[i];
			d++;
			i++;
		}
		append[d] = '\0';
		printf("String to be appended = %s\n", append);
		result = ft_strjoin(env_struct->envr, append);
		if (env_struct->envr != NULL)
			free(env_struct->envr);
		env_struct->envr = result;
		env_struct->hidden_flag = 0;
		printf("final appending result  = %s\n", env_struct->envr);
		return (1);
	}
	else
		env_struct->envr = malloc(1 * (ft_strlen(str) - i) + 1);
	while(str[i])
	{
		env_struct->envr[d] = str[i];
		d++;
		i++;
	}
	env_struct->envr[d] = '\0';
	return (1);
}

int	ft_search_env(t_env **env_struct, char *str)
{
	t_env	*ptr;
	int		i;
	int		d;
	char	*str_id;

	i = 0;
	d = 0;
	str_id = malloc(1 * ft_strlen_delim(str, '=') + 1);
	ptr = *env_struct;
	while(str[i] != '=' && str[i]) //fills up the env with only the id to compare
		{
			if (str[i] == '+')
			{
				i++;
				continue;
			}
			str_id[d] = str[i];
			d++;
			i++;
		}
	str_id[d] = '\0';
	i = 0;
	printf("ptr->opt = %s\n", str_id);
	while(ptr) //compares if the env allready exists
	{
		if (ft_strcmp(str_id, ptr->opt) == 0)
		{
			puts("im gonna be changed\n");
			i = ft_change_env(ptr, str); //if true it changes the value or appends 
			printf("%s-----%s\n", ptr->opt, ptr->envr);
			break;
		}
		ptr = ptr->next;
	}
	free(str_id);
	return (i);
}

void	ft_export(t_env **envr, t_vars *var)
{
	t_env	*ptr;
	int		i;
	int		d;
	char	**opt = ft_split(var->line_read, ' ');

	ptr = *envr;
	i = 0;
	d = 1;
	if (ft_count_vars(opt) == 1) //printing the env with quotes
	{
		print_env(*envr);
		return ;
	}
	while(opt[d])
	{
		if (ft_export_parser(opt[d], 0) == -1)
		{
			d++;
		 	continue ;
		}
		else if (ft_search_env(envr, opt[d]) == 1) //search if it exists return one if the value changed or appended thus return
		{
			d++;
			continue ;
		}
		while(ptr->next)
			ptr = ptr->next;
		ptr->next = malloc(sizeof(t_env) * 1);
		ptr = ptr->next;
		i = calc_size(opt[d], '=');
		if (opt[1][i] == '\0')
		{
			ptr->opt = malloc(1 * (i + 1));
			ptr->envr = NULL;
			ft_fillup(ptr, opt[d]);
			ptr->next = NULL; 
			continue ;
		}
		ptr->opt = malloc(1 * (i + 1));
		ft_fillup(ptr, opt[d]);
		ptr->envr = malloc(1 * (ft_strlen(opt[d]) - 1) + 1);
		ft_fillup_envr(ptr, opt[d]);
		ptr->hidden_flag = 0;
		ptr->next = NULL;
		ptr = *envr;
		d++;
	} 
}
