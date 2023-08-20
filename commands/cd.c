/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anchaouk <anchaouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 14:19:21 by anchaouk          #+#    #+#             */
/*   Updated: 2023/08/18 16:50:15 by anchaouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_add_oldpwd(t_env **envr, char *oldcwd) //updates oldpwd envr if dosent exist creates it
{
	t_env	*ptr;

	ptr = *envr;
	while (ptr)
	{
		if (ft_strcmp(ptr->name, "OLDPWD") == 0)
		{
			free(ptr->value);
			if (oldcwd != NULL)
				ptr->value = ft_strcpy_malloc(ptr->value, oldcwd);
			else
			{
				ptr->uninitialized = 0;
				ptr->value = NULL;
			}
			return ;
		}
		ptr = ptr->next;
	}
	ptr = *envr;
	while (ptr->next)
		ptr = ptr->next;
	ptr->next = malloc(sizeof(t_env) * 1);
	ptr = ptr->next;
	ptr->value = ft_strcpy_malloc(ptr->value, oldcwd);
	ptr->name = "OLDPWD";
	ptr->hidden_flag = 0;
	ptr->free_name = 1;
	ptr->free_value = 0;
	if (ptr->value == NULL)
		ptr->free_value = 1;
	ptr->next = NULL;
}

static int	ft_error_cd(int n, t_creat *res) // for errors
{
	if (n == 0)
	{
		ft_putstr_fd("cd: error retrieving current directory: getcwd: ", 2);
		ft_putstr_fd("cannot access parent directories: No such file or directory\n", 2);
	}
	else if (n == 1)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(res->opt[1], 2);
		ft_putstr_fd(": No such file or directory\n", 2);
	}
	return (n);
}

static int	ft_find_pwd(t_env **envr, t_creat *res) //updates pwd if getcwd fails it displays the deleted dir msg
{
	t_env	*ptr;
	int		flag;

	ptr = *envr;
	flag = 1;
	while (ptr)
	{
		if (ft_strcmp(ptr->name, "PWD") == 0)
		{
			if (getcwd(NULL, 0) == NULL)
			{
				ft_error_cd(0, res);
				ptr->value = ft_strjoin(ptr->value, "/");
				ptr->value = ft_strjoin(ptr->value, res->opt[1]);
				break ;
			}
			free(ptr->value);
			ptr->value = getcwd(NULL, 0);
			flag = 0;
			break ;
		}
		ptr = ptr->next;
	}
	return (0);
}

static int	ft_find_1pwd(t_env **envr, t_creat *res) //updates pwd if getcwd fails it displays the deleted dir msg
{
	t_env	*ptr;
	int		flag;

	ptr = *envr;
	flag = 1;
	while (ptr)
	{
		if (ft_strcmp(ptr->name, "1PWD") == 0)
		{
			if (getcwd(NULL, 0) == NULL)
			{
				ptr->value = ft_strjoin(ptr->value, "/");
				ptr->value = ft_strjoin(ptr->value, res->opt[1]);
				break ;
			}
			free(ptr->value);
			ptr->value = getcwd(NULL, 0);
			flag = 0;
			break ;
		}
		ptr = ptr->next;
	}
	return (0);
}

int	cd(t_creat *res, t_env **envr)
{
	t_env	*ptr;
	int		flag;

	ptr = *envr;
	flag = 0;
	while (ptr)
	{
		if (ft_strcmp(ptr->name, "PWD") == 0) // if pwd exists add it to oldpwd before its changed 
		{
			ft_add_oldpwd(envr, ptr->value);
			break;
		}
		else if (ft_strcmp(ptr->name, "OLDPWD") == 0)
		{
			ft_add_oldpwd(envr, NULL);
			break;
		}
		ptr = ptr->next;
	}
	if (chdir(res->opt[1]) == -1) //change dir if fails display error msg not found
	{
		flag = ft_error_cd(1, res); // return 1
		return (1);
	}
	flag = ft_find_pwd(envr, res); //updates the pwd and  checks if the deleted dir error is detected
	ft_find_1pwd(envr, res);
	return (flag);
}
