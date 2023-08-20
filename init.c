/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anchaouk <anchaouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 17:50:08 by anchaouk          #+#    #+#             */
/*   Updated: 2023/08/16 19:08:40 by anchaouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// initalizes the needed variables in the struct
void	init_vars(t_vars *var, char **env)
{
	g_exitstatus = 0;
	var->exitcode = 0;
	var->pipe_count = 0;
	var->failed_rd = 0;
	var->redirections_bool = -1;
	var->og_in = dup(0);
	var->og_out = dup(1);
	var->in = -1;
	var->out = -1;
	var->hd_pipe[0] = -1;
	var->hd_pipe[1] = -1;
	var->builtins = malloc(sizeof(char *) * 8);
	var->builtins[0] = "cd"; 
	var->builtins[1] = "echo";
	var->builtins[2] = "pwd";
	var->builtins[3] = "export";
	var->builtins[4] = "unset";
	var->builtins[5] = "env";
	var->builtins[6] = "exit";
	var->builtins[7] = NULL;
	var->envr = env;
}
