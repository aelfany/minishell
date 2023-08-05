/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelfany <abelfany@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 10:09:47 by abelfany          #+#    #+#             */
/*   Updated: 2023/08/05 12:58:14 by abelfany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"
void handler(int a)
{
    if(a != 18 && a != 3)
    {
        printf("\n");
        rl_on_new_line();
        rl_replace_line("", 0); 
        rl_redisplay();
    }
}


int main(int ac, char **av, char **env)
{
    (void)ac;
    (void)av;
	char    *s;
    char    d[100];
    t_vars    *var;
    t_env   *envr;
    envr = malloc(sizeof(t_env) * 1);
    var = malloc(sizeof(t_vars) * 1);
    init_vars(var, env);
    fill_env(envr, env);
    
    var->prevdir = getcwd(d, sizeof(d));
    rl_catch_signals = 0;
    signal(SIGINT, handler);
    signal(SIGTSTP, handler);
    signal(SIGQUIT, handler);
    while(1)
    {
        s = getcwd(d, sizeof(d));
        var->line_read =  readline("minishell\\> ");
        add_history(var->line_read);
        if (var -> line_read == NULL)
            exit(0);
        if (var -> line_read[0] == '\0')
            continue ;
        var->cmd_options = ft_split(var->line_read, ' ');
        // printf("%d\n",check_pipes(var));
        // pipe_calc(var);
        // // printf("%d\n", var->pipe_count);
        execute_cmd(var, envr);
        free(var->line_read);
        // wait(NULL);
    }
}