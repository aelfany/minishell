/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelfany <abelfany@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 10:09:43 by abelfany          #+#    #+#             */
/*   Updated: 2023/08/09 22:10:54 by abelfany         ###   ########.fr       */
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
// #include <errno.h>

// int __exitstatus = 0;
/*-------------by abelfany 1-------------*/

typedef struct s_var
{
    char    *str;
    int     save;
} t_var;



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
	struct	s_vars *next;
}	t_vars;

typedef struct s_env
{
	char	*envr; //holds the envr elements after the = equal sign
	char	*opt; // holds the id of the envr variable (before the equal sign)
	int		free_flag; 
	int		hidden_flag; // 1 hidden 0 available 
	char	*quoted_env; //holds the env in double quotes 
	char	*pwd_var; //everytime cd is used this variable gets updated 
	struct 	s_env *next; //pointer to the next element of the linked list which is another env element
} t_env;

typedef struct s_cmd
{
    char    *cmd;
    int     count;
    char    *token;
	int     heredoc;
    struct s_cmd *next;
} t_cmd;

typedef struct s_creat
{
    char    *cmd;
    char    *token;
	int     count;
    char    **opt;
    int     pipe;
    struct s_creat *next;
} t_creat;
/*-------------by abelfany 1-------------*/
// int     ft_cmp(char *s1, char *s2);
// char	*ft_strcpy(char *dest, char *src);
// char    *take_word(char *cmd);
int			not(char c);
int			ft_isalpha(int c);
int			ft_isascii(int c);
int			ft_isprint(int c);
int			ft_isspace(char c);
void 		error_handler(void);
t_creat		*append(t_creat *res);
int			skip_w_space(char *str);
int 		counter_quots(char *str);
char		*ft_strdup(const char *s1);
int			counter(char *str, char c);
char		*_remallc(char *str, char c);
t_creat		*read_string(char *str, t_env *envr);
void 		who_first(char *str, int *x, t_creat **res);
void		insert(t_creat **root, char *item, char *str);
void		take_string(char *str, int *x, t_creat **res);
void		check_expand(char *str, int *x, t_creat **res);
void		quots_handler(char *str, int *x, t_creat **res);
void 		rederction_apn(char *str, int *x, t_creat **res);
void		check_rederction(char *str, int *x, t_creat **res, char c);
/*-------------by abelfany 2-------------*/
// tool functions
char	**ft_split(char const *s, char c);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_itoa(int n);
char	*ft_strcpy_malloc(char *dest, char *src);
int		ft_strlen(const char *str);
int		ft_strlen_delim(char *str, char delim);
int		ft_strcmp(char *s1, char *s2);
// int		ft_cmp(const char *s1, const char *s2);
int		ft_atoi(const char *str);
int		calc_size(char *str, char delim);
void	ft_putstr_fd(char *str, int fd);
void	fill_env(t_env **envr, char **env); //fills up the env variable in vars struct
void	ft_fillup(t_env *str, char *env); // fills up the opt variable aka env id
void	ft_fillup_envr(t_env *str, char *env); // fills up the envr varibale aka whats after the = equal sign
char	*ft_getenv(t_env *envr, char *var); //finds the env in the env list i made
char	*my_get_env(t_env *envr, char *id); //finds an env var return its value else NULL
// exec functions
char	**path_finder(char **env);
char	*command_finder(char *cmd, char *env);
void	ft_error(char *str);
int		execute_cmd(t_vars *var, t_env **envr);
int		check_built_ins(t_vars *var);
void	init_vars(t_vars *var, char **env); //inits the vars struct
// commands
int 	cd(t_vars *var, t_env **envr);
int		pwd(t_env *envr);
int		echo(char **opt);
int		ft_exit(int	exitcode, t_env *env, t_vars *var);
void	ft_env(t_env *envr);
void	ft_export(t_env **envr, t_vars *var);
void	unset(t_env **envr, t_vars *var);
void	ft_exec(t_vars *var, int id);
// export functions
void	print_env(t_env *envr);
int		ft_export_parser(char *env, int n);
int		ft_count_vars(char **env);
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