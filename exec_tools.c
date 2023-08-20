/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anchaouk <anchaouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 20:01:44 by anchaouk          #+#    #+#             */
/*   Updated: 2023/08/18 18:19:19 by anchaouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*command_finder(char *cmd, char *env)
{
	char	**path;
	char	*fullcmd;
	int		i;
	int		d;

	path = ft_split(env, ':');
	fullcmd = NULL;
	i = 0;
	d = 0;
	if (env == NULL || cmd[0] == ' ')
		return (NULL);
	if (access(cmd, X_OK) == 0)
		return (cmd);
	while (path[i])
	{
		fullcmd = ft_strjoin(path[i], "/");
		fullcmd = ft_strjoin(fullcmd, cmd);
		if (access(fullcmd, X_OK) == 0)
			return (fullcmd);
		free (fullcmd);
		i++ ;
	}
	return (cmd);
}

void	exec_built_ins(int id, t_vars *var, t_env **envr, t_creat *res)
{
	int	fd;

	fd = -1;
	if (id == 0)
		g_exitstatus = cd(res, envr);
	else if (id == 1)
		g_exitstatus = echo(res->opt);
	else if (id == 2)
		g_exitstatus = pwd(*envr);
	else if (id == 3)
		ft_export(envr, res->opt, 1);
	else if (id == 4)
		unset(envr, res, 1, 1);
	else if (id == 5)
		ft_env(res->opt, *envr);
	else if (id == 6)
		ft_exit(var->exitcode, *envr, res, var);
}

void	execute_cmd(t_vars **var, t_env **envr, t_creat **res)
{
	int		id;
	char	*path;
	t_creat	*ptr;

	id = 0;
	path = ft_getenv(*envr, "PATH");
	ptr = *res;
	ft_open_redirections(res, var);
	while (ptr)
	{
		if ((*var)->failed_rd == -1)
			break ;
		if (check_pipes(*res) == 1)
			pipes_exec(*res, *var);
		else if (ft_strcmp(ptr->token, "CMD") == 0
			|| ft_strcmp(ptr->token, "DQ") == 0)
		{
			id = check_built_ins(ptr, *var);
			if (id != -1)
				exec_built_ins(id, *var, envr, ptr);
			else
				ft_exec(*envr, *res, 0);
		}
		ptr = ptr->next;
	}
}
