/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anchaouk <anchaouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 14:19:21 by anchaouk          #+#    #+#             */
/*   Updated: 2023/08/06 18:04:56 by anchaouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	 ft_add_oldpwd(t_env **envr, char *oldcwd) //updates oldpwd envr if dosent exist creates it
{
	t_env	*ptr;

	ptr = *envr;
	while (ptr)
	{
		if (ft_strcmp(ptr->opt, "OLDPWD") == 0)
		{
			 free(ptr->envr);
			 ptr->envr = ft_strcpy_malloc(ptr->envr, oldcwd);
			 return;
		}
		ptr = ptr->next;
	}
	ptr = *envr;
	while (ptr->next)
		ptr = ptr->next;
	ptr->next = malloc(sizeof(t_env) * 1);
	ptr = ptr->next;
	ptr->envr = ft_strcpy_malloc(ptr->envr, oldcwd);
	ptr->opt = "OLDPWD";
	ptr->hidden_flag = 0;
	ptr->next = NULL;
}

static int	ft_error_cd(int n, t_vars *var) // for errors
{
	if (n == 0)
	{
		ft_putstr_fd("cd: error retrieving current directory: getcwd: ", 2);
		ft_putstr_fd("cannot access parent directories: No such file or directory\n", 2);
	}
	else if (n == 1)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		perror(var->cmd_options[1]);
	}
	return (1);
}

static int	ft_find_pwd(t_env **envr, t_vars *var) //updates pwd if getcwd fails it displays the deleted dir msg
{
	t_env	*ptr;
	int		flag;

	ptr = *envr;
	flag = 1;
	while(ptr)
	{
		if (ft_strcmp(ptr->opt, "PWD") == 0)
		{
			if (getcwd(NULL,0) == NULL)
			{
				ft_error_cd(0, var);
				ptr->envr = ft_strjoin(ptr->envr, "/");
				ptr->envr = ft_strjoin(ptr->envr, var->cmd_options[1]);
				break;
			}
			free(ptr->envr);
			ptr->envr = getcwd(NULL, 0);
			flag = 0;
			break;
		}
		ptr = ptr->next;
	}
	return (flag);
}

int	cd(t_vars *var, t_env **envr)
{
	t_env	*ptr;
	int		flag;
	
	ptr = *envr;
	flag = 0;
	while(ptr)
	{
		if (ft_strcmp(ptr->opt, "PWD") == 0) // if pwd exists add it to oldpwd before its changed 
			ft_add_oldpwd(envr, ptr->envr);
		ptr = ptr->next;
	}
	if(chdir(var->cmd_options[1]) == -1) //change dir if fails display error msg not found
	{
		flag = ft_error_cd(1, var); // return 1
		return (1);
	}
	flag = ft_find_pwd(envr, var); //updates the pwd and  checks if the deleted dir error is detected
	return (flag);
}
