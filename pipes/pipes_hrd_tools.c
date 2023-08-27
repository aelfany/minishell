/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_hrd_tools.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anchaouk <anchaouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 21:52:27 by anchaouk          #+#    #+#             */
/*   Updated: 2023/08/21 22:32:30 by anchaouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	hrd_handler(int a)
{
	if (a == 2)
		exit(1);
	else if (a == 3)
		return ;
}

void	hrd_signal_reset(int pid)
{
	if (pid != 0)
	{
		signal(SIGINT, hrd_handler);
		signal(SIGQUIT, hrd_handler);
	}
}
