/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anchaouk <anchaouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 17:50:08 by anchaouk          #+#    #+#             */
/*   Updated: 2023/08/23 13:11:59 by anchaouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// initalizes the needed variables in the struct

void	init_vars(t_vars *var, char **env, t_env **envr)
{
	var->p_in = 0;
	var->p_out = 0;
	var->i = 0;
	var->p_hrd = 0;
	var->pipe_in = NULL;
	var->pipe_out = NULL;
	var->pipe_hrd = NULL;
	var->pipe_count = 0;
	var->cmd_count = 0;
	g_exitstatus = 0;
	var->exitcode = 0;
	var->og_in = -1;
	var->og_out = -1;
	var->pipe_count = 0;
	var->failed_rd = 0;
	var->redirections_bool = -1;
	var->in = -1;
	var->out = -1;
	var->hd_pipe[0] = -2;
	var->hd_pipe[1] = -2;
	var->envr = env;
	fill_env(envr, env, 0, 0);
}
