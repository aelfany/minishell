/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelfany <abelfany@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 14:20:31 by abelfany          #+#    #+#             */
/*   Updated: 2023/08/17 18:38:19 by abelfany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int find_last(char *str, int *flag, char c)
{
    int a;

    a = 1;
    int f = 0;
    while (str[a])
    {
        if (str[a] == c)
        {
            f = 1;
            break;
        }
        a++;
    }
    (*flag) = f;
    return (a);
}
int counter_quots(char *str)
{
    int b;
    int flag;
    
    b = 0;
    while (str[b])
    {
        if (str[b] == '"' || str[b] == '\'')
        {
            b += find_last(str+b, &flag, str[b]);
            if (flag == 0)
                return (1);
        }
        b++;
    }
    return (0);
}

char *quts(char *str, int *x, t_env *env)
{
    int b = x[0];
    char flag;
    char *word;
    (void)env;
    // char *join;
    
    flag = '\'';
    if (str[b] == '"')
        flag = '"';
    word = malloc(2);
    word[0] = 0;
    b++;
    while (str[b] != flag && str[b] && not_2(str[b]))
    {
        if(str[b] == '$')
        {
            expand_inside_dq(str, &b, env);
        }
        word = _remallc(word, str[b]);
        if(!str[b])
            break; 
        b++;
    }
    (*x) = b;
    return (word);  
}

// char *qt_expand(char *str, int *x, t_env *env)
// {
//     int b = x[0];
//     char flag;
//     char *word;
//     char *join;
    
//     flag = '\'';
//     if (str[b] == '"')
//         flag = '"';
//     word = malloc(2);
//     word[0] = 0;
//     b++;
//     while (str[b] != flag && str[b] && not_2(str[b]))
//     {
//         if(str[b] == '$')
//         {
//             join = check_expand(str, &b, env);
//             word = ft_strjoin(word, join);
//         }
//         word = _remallc(word, str[b]);
//         b++;
//     }
//     (*x) = b;
//     // printf("%s\n", word);
//     return (word);  
// }

void add_back_token(t_creat **res, char *word, char flag)
{
    if (flag == '\'')
        insert(res, word, "HRD_SQ");
    else if (flag == '"')
        insert(res, word, "HRD_DQ");
    else if (flag == ' ')
        insert(res, word, "HRD");
    // free(word);
}

int not_2(char c)
{
    if(c == '|' || c == '<' || c == '>')
        return (0);
    return (1);
}

void check_heredoc(char *str, int *x, t_creat **res, t_env *env)
{
    t_var u;
    
    (void)env;
    u.flag = ' ';
    u.word = malloc(2);
    u.word[0] = 0;
    u.b = x[0] + 2;
    while (ft_isspace(str[u.b]))
        u.b++;
    u.count = u.b;
    while (str[u.count] == '$')
        u.count++;
    u.count -= u.b;
    while (str[u.b] && !ft_isspace(str[u.b]) && not_2(str[u.b]))
    {
        if (str[u.b] == '$' && (str[u.b + 1] == '"' \
        || str[u.b + 1] == '\'') && u.count % 2)
            u.b++;
        if ((str[u.b] != '"' && str[u.b] != '\''))
           u.word = _remallc(u.word, str[u.b]);
        else
        {
            u.flag = str[u.b];
            u.join = quts(str, &u.b, env);
            u.word = ft_strjoin(u.word, u.join);
        }
        u.b++;
    }
    (*x) = u.b;
    add_back_token(res, u.word, u.flag);
}

int not_red(char c)
{
    if(c == '\'' || c == '"' || c == '|'||c == '<' 
        || c == '>' || c == '$')
        return (0);
    return (1);
}

t_creat *read_string(char *str, t_env *envr)
{
    t_creat *res;
    int count;
    int x;
    (void)envr;

    count = 0;
    res = NULL;
    x = skip_w_space(str);
    while (str[x])
    {
        if (counter_quots(str) || counter(str+x, '|') > 1)
        {
            error_handler();
            break ;
        }
        if (not(str[x]))
            take_string(str, &x, &res, envr);
        if (!counter_quots(str) && (str[x] == '\'' || str[x] == '"'))
            who_first(str, &x, &res, envr);
        if (str[x] == '<' && str[x + 1] == '<')
            check_heredoc(str, &x, &res, envr);
        if (str[x] == '>' && str[x + 1] == '>')
            rederction_apn(str, &x, &res, envr);
        if (str[x] == '>' && str[x + 1] != '>')
            check_rederction(str, &x, &res, '>', envr);
        if (str[x] == '<' && str[x + 1] != '<')
            check_rederction(str, &x, &res, '<', envr);
        if (str[x] == '|')
        {
            insert(&res, "|", "PIP");
            x++;
        }
        if (str[x] == '$')
            check_expand(str+x, &x, &res, envr);
        if (!str[x])
            break;
        if (not_red(str[x]) || ft_isspace(str[x]) || str[x] == '$')
            x++;
    }
    return (append(res));
}