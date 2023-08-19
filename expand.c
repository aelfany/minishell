/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelfany <abelfany@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 22:34:23 by abelfany          #+#    #+#             */
/*   Updated: 2023/08/19 03:49:04 by abelfany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int check_expand_cases(char *str, int x)
{
    
    if (str[x] == '$' && str[x + 1] == '*')
        return (1);
    return 0;
}

char *expand(t_env *env, int count, char *word)
{
    int a;

    a = -1;
    while (env)
    {
        if (!ft_strcmp(env -> opt, word))
        {
            if (count % 2)
            {
                word = malloc(2);
                word[0] = 0;
                while (env -> envr[++a])
                    word = _remallc(word, env -> envr[a]);
            }
            return (word);
        }
        env = env -> next;
    }
    if (env == NULL && count % 2)
        word[0] = 0;
    return (word);
}

void error_hh(char *str)
{
    ft_putstr_fd(str, 2);
    exit(0);
}

char *quots_expand(char *str, int *x, t_env *env)
{
    int b = x[0];
    char flag;
    char *word;
    char *join;
    
    flag = '\'';
    if (str[b] == '"')
        flag = '"';
    word = malloc(2);
    word[0] = 0;
    while (str[b] && !ft_isspace(str[b]))
    {
        if(str[b] == '"' || str[b] == '\'')
        {
            join = quts(str, &b, env);
            word = ft_strjoin(word, join);
        }
        else
            word = _remallc(word, str[b++]);
        if(!str[b] || !not_2(str[b]) || str[b] == '$' || ft_isspace(str[b]))
            break ;
        b++;
    }
    (*x) = b;
    return word;
}

int is_yes(char c)
{
    if(c == '|' || c == '<' || c == '>' || ft_isspace(c))
        return (1);
    return (0);
}
char	*check_expand_rd(char *str, int *x, t_env *env)
{
    int a;
    char *word;
    char *join;

    a = x[0];
    word = 0;
    while(str[a])
    {
        if(is_yes(str[a]))
            break;
        if(str[a] == '"' || str[a] == '\'')
        {
            join = quots_expand(str, &a, env);
            word = ft_strjoin(word, join);
            
        }
        if(str[a] == '$')
        {
            join = take_expand_word(str, &a, env);
            word = ft_strjoin(word, join);
        }
    }
    (*x) = a;
    return word;
}

// char *remove_qt(char *str)
// {
//     int b;
//     char flag;
//     char *word;
    
//     flag = '\'';
//     b = 0;
//     if (str[b] == '"')
//         flag = '"';
//     word = malloc(2);
//     word[0] = 0;
//     b++;
//     while (str[b] != flag && str[b] && not_2(str[b]))
//     {
//         word = _remallc(word, str[b]);
//         if(!str[b])
//             break ;
//         b++;
//     }
//     return (word);  
// }

// char *overwrite(char *qt, char *str, char *word, int size)
// {
//     char *over;
//     int a;

//     a = 0;
//     (void)word;
//     (void)qt;
//     over = malloc((ft_strlen(str) + size + 1) * sizeof(char));
//     return str;
// }

// long long deff(long long a, long long b)
// {
//     if (a >= b)
//         return (a - b);
//     return (b * -1);
// }

// char *expand_inside_dq(char *str, int *x, t_env *env)
// {
//     int a;
//     char *word;

//     a = x[0];
//     word = take_expand_word(str, &a, env);
//     (*x) = a;
//     return (str);
// }

int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	return (0);
}

int if_expand(char c)
{
    if(c == '-' || c == '*' || ft_isdigit(c) || ft_isspace(c))
        return (1);
    return (0);
}

// int special_cases(char c)
// {
    
// }
char *take_expand_word(char *str, int *x, t_env *env)
{
    int b;
    char *word;
    int count;

    
    word = malloc(2);
    word[0] = 0;
    count = 0;
    b = x[0] - 1;
    while(str[++b] == '$')
        count++;
    // if(special_cases(str[b]))
    // {
        
    // }   
    while (str[b] && not(str[b]))
        word = _remallc(word, str[b++]);
    if (count % 2 && word[0] == 0)
        return((*x) = b, _remallc(word, '$'));
    word = expand(env, count, word);
    (*x) = b;
    return word;
}

void check_expand(char *str, int *x, t_creat **res, t_env *env)
{
    int a;
    char *word;
    char *join;

    a = x[0];
    while(str[a])
    {
        if(is_yes(str[a]))
            break;
        if(str[a] == '"' || str[a] == '\'')
        {
            join = quots_expand(str, &a, env);
            word = ft_strjoin(word, join);
        }
        if(str[a] == '$')
        {
            join = take_expand_word(str, &a, env);
            word = ft_strjoin(word, join);
        }
    }
    (*x) = a;
    insert(res, word, "CMD", 0);
}
