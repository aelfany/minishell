/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelfany <abelfany@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 10:09:47 by abelfany          #+#    #+#             */
/*   Updated: 2023/08/27 13:47:51 by abelfany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exitstatus = 0;

// void	free_me(t_creat *res)
// {
// 	t_creat	*ptr;

// 	ptr = res;
// 	while (ptr)
// 	{
// 		free(ptr->cmd);
// 		free(ptr->opt);
// 		ptr = ptr->next;
// 	}
// }

void	ft_reset_fd(t_vars **var, t_creat *res)
{
	(void)res;
	ft_close_all_rd(*var);
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
	(*var)->in = -1;
	(*var)->out = -1;
	(*var)->failed_rd = 0;
	free((*var)->line_read);
	// if (res != NULL)
	// {
	// 	if (res->cmd != NULL)
	// 		free(res->cmd);
	// 	free(res->token);
	// }
}

void	handler(int a)
{
	if (a != 3)
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
	signal(SIGQUIT, SIG_IGN);
}

void print_list(t_creat *res)
{
	while(res)
	{
		printf("type[%s] %s\n", res->token, res->cmd);
		res = res->next;
	}
}

void	free_list(t_creat **save)
{
	t_creat *tmp;
	
	while ((*save) -> next)
	{
		tmp = (*save);
		(*save) = (*save)-> next;
		ft_free2(tmp);
	}
	ft_free2((*save));
}

void free_dob(char **str)
{
	int a;

	a = 1;
	while(str[a])
	{
		free(str[a]);
		a++;
	}
	free(str);
}

void	free_last_list(t_creat **save)
{
	t_creat *tmp;
	
	while ((*save) -> next)
	{
		tmp = (*save);
		if((*save) -> opt != NULL)
			free_dob((*save) -> opt);
		tmp = (*save);
		(*save) = (*save)-> next;
		ft_free2(tmp);
	}
	ft_free2((*save));
}

int	main(int ac, char **av, char **env)
{
	t_creat	*res;
	t_vars	*var;
	t_creat	*list;
	t_env	*envr;
	t_creat	*tmp;

	(void)ac;
	(void)av;
	(void)tmp;
	list = NULL;
	envr = malloc(sizeof(t_env) * 1);
	if (envr == NULL)
		return (0);
	var = malloc(sizeof(t_vars) * 1);
	if (var == NULL)
		return (0);
	init_vars(var, env, &envr);
	while (1)
	{
		signals();
		var->line_read = readline("minishell\\> ");
		if (var -> line_read == NULL)
			exit(0);
		if (var -> line_read[0] == '\0')
			continue ;
		res = read_string(&list, var->line_read, envr);
		if(var->line_read != NULL)
			add_history(var->line_read);
		if(list != NULL)
			free_list(&list);
		// free_last_list(&res);
		// tmp = res;
		// print_list(res);
		// print_list(res);
		if (check_pipes(res) != 1)
			ft_open_heredocs(&res, &var, envr);
		execute_cmd(&var, &envr, &res);
		ft_reset_fd(&var, res);
		while(res)
		{
			tmp = res;
			if (res -> opt)
				free_dob(res -> opt);
			tmp = res;
			res = res -> next;
			ft_free2(tmp);
		}
		// res = tmp;
		// free(var->line_read);
	}
}
