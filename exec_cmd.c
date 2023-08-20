/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anchaouk <anchaouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 15:27:15 by anchaouk          #+#    #+#             */
/*   Updated: 2023/08/18 17:38:14 by anchaouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//	if (g_exitstatus == 2) // cmd exited with ctl-c
//	if (g_exitstatus == 3) // cmd exited with ctl- backslash

void	exitstatus_handler(int status)
{
	if (WIFEXITED(status) != 0)
		g_exitstatus = WEXITSTATUS(status);
	else if (WIFSIGNALED(status) != 0)
	{
		g_exitstatus = WTERMSIG(status);
		if (g_exitstatus == 2)
			g_exitstatus = 130; 
		if (g_exitstatus == 3)
			g_exitstatus = 131;
	}
}

static void	ft_error_exec(t_creat *res, char *cmd, int flag)
{
	int	i;
	DIR	*d;

	i = 0;
	d = opendir(cmd);
	if (d != NULL)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(res->cmd, 2);
		ft_putstr_fd(": is a directory\n", 2);
		closedir(d);
		if (flag == 1)
			exit(126);
		free(cmd);
	}
	else if (access(cmd, X_OK) != 0)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(res->cmd, 2);
		ft_putstr_fd(": command not found\n", 2);
		if (flag == 1)
			exit(127);
		free(cmd);
	}
}

static char	**fillup_exec_env(t_env *envr, int i)
{
	t_env	*ptr;
	char	**env;

	ptr = envr;
	env = NULL;
	while (ptr)
	{
		ptr = ptr->next;
		i++;
	}
	ptr = envr;
	env = malloc(sizeof(char *) * (i + 1));
	if (!env)
		exit(-1);
	i = 0;
	while (ptr)
	{
		env[i] = ft_strjoin(ptr->name, "=");
		env[i] = ft_strjoin(env[i], ptr->value);
		i++;
		ptr = ptr->next;
	}
	env[i] = NULL;
	return (env);
}

void	ft_execute_help(char *cmd, char **opt, char **env, t_creat *res)
{
	int	p_id;
	int	status;

	p_id = fork();
	if (p_id == 0)
	{
		if (execve(cmd, opt, env) == -1)
			ft_error_exec(res, cmd, 1);
	}
	waitpid(-1, &status, 0);
	exitstatus_handler(status);
}

void	ft_exec(t_env *envr, t_creat *res, int i)
{
	char	**env;
	char	*cmd;
	t_env	*ptr;

	ptr = envr;
	env = fillup_exec_env(envr, 0);
	cmd = NULL;
	if (res->cmd[0])
		cmd = command_finder(res->cmd, my_get_env(envr, "PATH"));
	if (cmd == NULL)
	{
		ft_error_exec(res, res->cmd, 0);
		g_exitstatus = 127;
		return ;
	}
	ft_execute_help(cmd, res->opt, env, res);
	i = 0;
	while (env[i++])
		free(env[i]);
}
