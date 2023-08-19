/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelfany <abelfany@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 14:19:37 by abelfany          #+#    #+#             */
/*   Updated: 2023/08/19 03:49:39 by abelfany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
// void check_rederction(char *str, int *x, t_creat **res, char c)
// {
//     int b;
//     char *word;

//     b = x[0];
//     word = malloc(2);
//     word[0] = 0;
//     b = x[0];
//     b = b + skip_space(str+b+1)+1;
//     while (!ft_isspace(str[b]) && str[b] && not(str[b]))
//     {
//         word = _remallc(word, str[b]);
//         b++;
//     }
//     (*x) = b;
// }
// void rederction_apn(char *str, int *x, t_creat **res)
// {
//     int b;
//     char *word;

//     b = x[0];
//     word = malloc(2);
//     word[0] = 0;
//     b = x[0] + 2;
//     while(ft_isspace(str[b]))
//         b++;
//     while (str[b] && !ft_isspace(str[b]) && not(str[b]))
//     {
//         word = _remallc(word, str[b]);
//         b++;
//     }
//     (*x) = b;
//     insert(res, word, "RD_AP");
// }

int skip_space(char *str)
{
    int a;

    a = 0;
    while (str[a] == '\t' || str[a] == '\n' ||  str[a] == '\v' 
        ||  str[a] == '\f' || str[a] == '\r' || str[a] == ' ')
    {
        a++;
    }
    return (a);
}

void add_red_token(t_creat **res, char *word, char c)
{
    if (c == '<')
        insert(res, word, "RDIN", 0);
    else if (c == '>')
        insert(res, word, "RDOUT", 0);
}

void check_rederction(char *str, int *x, t_creat **res, char c, t_env *env)
{
    int b;
    char *word;
    char *join;
    
    word = malloc(2);
    word[0] = 0;
    b = x[0] + 1;
    while (ft_isspace(str[b]))
        b++;
    while (str[b] && !ft_isspace(str[b]) && not_2(str[b]))
    {
        if(str[b] == '$')
        {
            join = take_expand_word(str, &b, env);
            word = ft_strjoin(word, join);
        }
        while(not_2(str[b]) && str[b] && (str[b] != '"' 
            && str[b] != '\'') && !ft_isspace(str[b]))
           word = _remallc(word, str[b++]);
        if(str[b] && !ft_isspace(str[b]) && not_2(str[b]))
        {
            join = quts(str, &b, env);
            word = ft_strjoin(word, join);
        }
        if(!str[b] || ft_isspace(str[b]) || !not_2(str[b]))
            break ;
        b++;
    }
    (*x) = b;
    add_red_token(res, word, c);
}
// <$"$USER""HELLO"'"a"''word'<<hello
void rederction_apn(char *str, int *x, t_creat **res, t_env *env)
{
    int b;
    char *word;
    char *join;
    
    word = malloc(2);
    word[0] = 0;
    b = x[0] + 2;
    while (ft_isspace(str[b]))
        b++;
    while (str[b] && !ft_isspace(str[b]) && not_2(str[b]))
    {
        if(str[b] == '$')
        {
            join = take_expand_word(str, &b, env);
            word = ft_strjoin(word, join);
        }
        while(not_2(str[b]) && str[b] && (str[b] != '"' 
            && str[b] != '\'') && !ft_isspace(str[b]))
           word = _remallc(word, str[b++]);
        if(str[b] && !ft_isspace(str[b]) && not_2(str[b]))
        {
            join = quts(str, &b, env);
            word = ft_strjoin(word, join);
        }
        if(!str[b] || ft_isspace(str[b]) || !not_2(str[b]))
            break ;
        b++;
    }
    (*x) = b;
    insert(res, word, "RD_AP", 0);
}
