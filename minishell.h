/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelfany <abelfany@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 10:09:43 by abelfany          #+#    #+#             */
/*   Updated: 2023/07/29 16:46:18 by abelfany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _MINISHELL_H
# define _MINISHELL_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
// #include "../libft/libft.h"
#include <fcntl.h>
#include <dirent.h>
#include <readline/readline.h>
#include <readline/history.h>

/*-------------by abelfany 1-------------*/
#define OPT 0
#define CMD 0
#define RDIN 0
#define RDOUT 0
#define TBLONIT
typedef struct s_var
{
    char    *str;
    int     save;
} t_var;

typedef struct s_cmd
{
    char    *s_cmd;
    // char    **cmd;
	int pipe;
    struct s_env *next;
} t_cmd;

typedef struct s_garbage
{
    void    *coll;
    void    **coll2;
    struct s_garbage *next;
} t_garbage;

/*-------------by abelfany 2-------------*/

typedef struct s_vars
{
	char	*line_read; //line read from input
	char	*cmd; //the splited command
	char	**cmd_options; //the splited command options
	char	**test;
	char	**op;
	char	**op1;
	char	**op2;
	char	**builtins; //pointer to builtin names 
	char	**envr; //holds the env variables
	char	*prevdir; //holds the previous visited directory
	int		exitcode;
	int		pipe_count; //holds how many pipes are there
	int		cmd_count; //holds the command count
	int		(*pipe)[2]; //holds the open filedes of open pipes 
	int		*pid; //holds id of open processes
	int		i; //integer used as an index in some cases
	int		redirections_bool; //boolean used to check if redirections exist originally set to -1
}	t_vars;

typedef struct s_env
{
	char	*envr;
	char	*opt;
	int		index;
	char	*quoted_env;
	struct 	s_env *next;
} t_env;

/*-------------by abelfany 1-------------*/
int     ft_cmp(char *s1, char *s2);
char	*ft_strcpy(char *dest, char *src);
char    *take_word(char *cmd);
/*-------------by abelfany 2-------------*/
// tool functions
char	**ft_split(char const *s, char c);
char	*ft_strjoin(char const *s1, char const *s2);
int		ft_strlen(const char *str);
int		ft_strcmp(char *s1, char *s2);
// int		ft_cmp(const char *s1, const char *s2);
int		ft_atoi(const char *str);
int		calc_size(char *str, char delim);
void	fill_env(t_env *envr, char **env); //fills up the env variable in vars struct
void	ft_fillup(t_env *str); //used by export builtin
// exec functions
char	**path_finder(char **env);
char	*command_finder(char *cmd, char *env);
void	ft_error(char *str);
int		execute_cmd(t_vars *var, t_env *envr);
int		check_built_ins(t_vars *var);
void	init_vars(t_vars *var, char **env); //inits the vars struct
// commands
int 	cd(t_vars *var);
int		pwd();
int		echo(char **opt);
int		ft_exit(int	exitcode, t_env *env, t_vars *var);
void	ft_env(t_env *envr);
void	ft_export(t_env *envr, t_vars *var);
void	unset(t_env *envr, t_vars *var);
void	ft_exec(t_vars *var);
// pipe functions
void	ft_pipe(t_vars *var);
void	pipe_calc(t_vars *var);
void	ft_execone(int	*end, t_vars *var);
void	ft_execpipe(int *end1, int *end0, t_vars *var);
void	ft_exectwo(int *end, t_vars *var);
void	ft_close_first(int end[][2],t_vars *var);
void	ft_close_last(int end[][2], t_vars *var);
void	ft_close_pipe(int end[][2], t_vars *var);
int		check_pipes(t_vars *var);
int		pipes_exec(t_vars *var);
void	ft_close_all(t_vars *var);
// checking functions
int	ft_check_redirections(t_vars *var);
#endif