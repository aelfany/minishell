 /* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anchaouk <anchaouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 20:01:44 by anchaouk          #+#    #+#             */
/*   Updated: 2023/05/23 14:06:46 by anchaouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**path_finder(char **env)
{
	int		i;
	int		d;
	char	*path;
	char	**result;

	i = 0;
	d = 0;
	path = "PATH";
	while (env[i])
	{
		if (env[i][d] == path[d])
			d++;
		else if (path[d] == '\0')
			break ;
		else if (env[i][d] != path[d])
			i++;
		else
			d = 0;
	}
	result = ft_split(env[i], ':');
	return (result);
}

char	*command_finder(char *cmd, char *env)
{
	char	**path;
	char	**cmnd;
	char	*fullcmd;
	int		i;
	int		d;
	char	*slsh;

	path = ft_split(env, ':');
	cmnd = ft_split(cmd, ' ');
	i = 0;
	d = 0;
	if (cmnd[0][0] == '<')
		d = 2;
	slsh = "/ .";
	if (access(cmnd[0], X_OK) == 0)
		return (cmnd[0]);
	else if (cmnd[0][0] == slsh[0])
		ft_error(cmnd[0]);
	if (cmnd[0][0] == slsh[2])
		ft_error(cmnd[0]);
	while (path[i])
	{
		fullcmd = ft_strjoin(path[i], "/");
		fullcmd = ft_strjoin(fullcmd, cmnd[d]);
		if (access(fullcmd, X_OK) == 0)
			return (fullcmd);
		free (fullcmd);
		i++ ;
	}
	return (cmnd[0]);
}

void	ft_error(char *str)
{
	perror(str);
	exit(1);
}

void	exec_built_ins(int id, t_vars *var, t_env *envr)
{
	int	f_id;
	int	fd;

	fd = -1;
	f_id = 1;
	if (var->cmd_options[0][0] == '<')
	{
		fd = ft_check_redirections(var);
		f_id = fork();
		if (f_id == -1 || fd == -1)
		{
			printf("error\n");
			exit(1);
		}
		dup2(0, fd);
	}
	if (id == 0)
		cd(var);
	else if (id == 1)
		echo(var->cmd_options);
	else if (id == 2)
		pwd();
	else if (id == 3)
		ft_export(envr, var);
	else if (id == 4)
		unset(envr, var);
	else if (id == 5)
		ft_env(envr);
	else if (id == 6)
		ft_exit(var->exitcode, envr, var);
	if (f_id == 0)
	{
		close(fd);
		exit(0);
	}
}

int	execute_cmd(t_vars *var, t_env *envr)
{
	int	id;
	int	pipe_id;

	id = 0;
	var->cmd = command_finder(var->line_read, getenv("PATH"));
    var->cmd_options = ft_split(var->line_read, ' ');
	pipe_id = 0;
	pipe_id = check_pipes(var);
	var->cmd_count = 2;
	if	(pipe_id == 1)	// checks if pipe exists
		pipes_exec(var);
	id =  check_built_ins(var);	// checks if builtins
	if (id != -1 && pipe_id != 1)
	{
		printf("builtin\n");
		exec_built_ins(id, var, envr);
	}
	
	else if (id == -1 && pipe_id != 1) // checks if neither pipe or builtin
		ft_exec(var);
	return (0);
}
