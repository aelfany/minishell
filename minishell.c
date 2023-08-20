/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelfany <abelfany@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 10:09:47 by abelfany          #+#    #+#             */
/*   Updated: 2023/08/20 03:26:42 by abelfany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exitstatus = 0;

void	free_me(t_creat *res)
{
	t_creat	*ptr;

	ptr = res;
	while (ptr)
	{
		free(ptr->cmd);
		free(ptr->opt);
		ptr = ptr->next;
	}
}

static void	ft_reset_fd(t_vars **var)
{
	dup2((*var)->og_in, 0);
	dup2((*var)->og_out, 1);
	close((*var)->og_in);
	close((*var)->og_out);
	close((*var)->out);
	close((*var)->in);
	close((*var)->hd_pipe[0]);
	close((*var)->hd_pipe[1]);
	(*var)->hd_pipe[0] = -1;
	(*var)->hd_pipe[1] = -1;
	(*var)->og_in = dup(0);
	(*var)->og_out = dup(1);
	(*var)->in = -1;
	(*var)->out = -1;
	(*var)->failed_rd = 0;
	free((*var)->line_read);
}

void	handler(int a)
{
	if (a != 3 && a != 18)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0); 
		rl_redisplay();
	}
}

void	signals(void)
{
	signal(SIGINT, handler);
	signal(SIGTSTP, handler);
}

int	main(int ac, char **av, char **env)
{
	t_creat	*res;
	t_vars	*var;
	t_env	*envr;
	t_creat	*sv;

	(void)ac;
	(void)av;
	envr = malloc(sizeof(t_env) * 1);
	var = malloc(sizeof(t_vars) * 1);
	init_vars(var, env);
	fill_env(&envr, env, 0, 0);
	rl_catch_signals = 0;
	signals();
	while (1)
	{
		var->line_read = readline("minishell\\> ");
		add_history(var->line_read);
		if (var -> line_read == NULL)
			exit(0);
		if (var -> line_read[0] == '\0')
			continue ;
		res = read_string(var->line_read, envr);
		sv = res;
		while (res)
		{
			printf("type [%s] %s\n", res -> token, res -> cmd);
			res = res -> next;
		}
		res = sv;
		ft_open_heredocs(&res, &var);
		execute_cmd(&var, &envr, &res);
		ft_reset_fd(&var);
		free_me(res);
	}
}
