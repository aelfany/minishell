/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelfany <abelfany@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 14:19:21 by anchaouk          #+#    #+#             */
/*   Updated: 2023/07/18 15:25:20 by abelfany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	cd(t_vars *var)
{
	char	*d;
	char	*path;

	d = NULL;
	d = getcwd(d, sizeof(d));
	if (!var->cmd_options[1])
		chdir(getenv("ZDOTDIR"));
	else if (ft_strlen(var->cmd_options[0]) == 2
		&& var->cmd_options[1][0] == '-')
		chdir(getenv("OLDPWD"));
	else if (ft_strlen(var->cmd_options[0]) == 2
		&& var->cmd_options[1][0] == '~')
			chdir(getenv("ZDOTDIR"));
	else if (var->cmd_options[1][0] != '/' && var->cmd_options[1][0] != '.')
	{
		path = ft_strjoin("/", var->cmd_options[1]);
		chdir(ft_strjoin(d, path));
		free(path);
	}
	else if (var->cmd_options[1][0] == '.')
		chdir(var->cmd_options[1]);
	else if (var->cmd_options[1][0] == '/')
		chdir(ft_strjoin(d, var->cmd_options[1]));
	free(d);
	return (0);
}
