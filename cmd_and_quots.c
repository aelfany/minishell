/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_and_quots.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelfany <abelfany@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 09:59:47 by abelfany          #+#    #+#             */
/*   Updated: 2023/08/19 03:49:25 by abelfany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *_remallc(char *str, char c)
{
    char *save;
    int a;
    
    a = -1;
    save = malloc(strlen(str)+1);
    while(str[++a])
        save[a] = str[a];
    // free(str);
    save[a] = 0;
    str = malloc((strlen(str) + 2) * sizeof(char));
    str[strlen(save)] = c;
    str[strlen(save)+1] = 0;
    a = -1;
    while (save[++a])
        str[a] = save[a];
    free(save);
    return (str);
}

// char *who_first(char *word, char *str, int *x, int *tab)
// {
//     int b;

//     b = 0;
//     while(tab[0] < tab[1] && str[tab[0]] && str[b])
//     {
//         if(ft_isascii(str[tab[0]]) && (str[tab[0]] != '"' && str[tab[0]] != '\''))
//             word = _remallc(word, str[tab[0]]);
//         tab[0]++;
//         b++;
//     }
//     (*x) = tab[1];
//     return (word);
// }

int not_3(char c)
{
    if(c == '|' || c == '<' || c == '>')
        return (0);
    return (1);
}

void who_first(char *str, int *x, t_creat **res, t_env *env)
{
    int b = x[0];
    char flag;
    char *word;
    char *join;
    
    (void)env;
    flag = '\'';
    if (str[b] == '"')
        flag = '"';
    word = malloc(2);
    word[0] = 0;
    while (str[b] && !ft_isspace(str[b]))
    {
        if(str[b] == '$')
        {
            join = take_expand_word(str, &b, env);
            word = ft_strjoin(word, join);
        }
        if(str[b] == '"' || str[b] == '\'')
        {
            join = quts(str, &b, env);
            word = ft_strjoin(word, join);   
        }
        else if(str[b] != '$' && not_2(str[b]) && str[b])
            word = _remallc(word, str[b]);
        if(!str[b] || !not_2(str[b]) || ft_isspace(str[b]))
            break ;
        b++;
    }
    (*x) = b;
    insert(res, word, "CMD", 0);
}
// void quots_handler(char *str, int *x, t_creat **res)
// {
//     int b;
//     char flag;
//     char *word;
//     int tab[2];

//     flag = 'x';
//     b = x[0];
//     word = malloc(2);
//     word[0] = 0;
//     while(str[b] && str[b] != ' ')
//     {
//         tab[0] = b;
//         if (str[b] == '"')
//             flag = '"';
//         else
//             flag = '\'';
//         while(str[++b] != flag && str[b]);
//         tab[1] = b;
//         word = who_first(word, str, &b, tab);
//         b++;
//     }
//     (*x) = b - 1;
// }

// void take_string(char *str, int *x, t_creat **res)
// {
//     int b;
//     char *word;

//     word = malloc(2);
//     word[0] = 0;
//     b = x[0];
//     while (str[b] && !ft_isspace(str[b]) && not(str[b]))
//     {
//         word = _remallc(word, str[b]);
//         b++;
//     }
//     (*x) = b;
//     insert(res, word, "CMD");
// }
// void rederction_apn(char *str, int *x, t_creat **res)

void take_string(char *str, int *x, t_creat **res, t_env *env)
{
    int     b;
    char    flag;
    char    *word;
    char    *join;
    
    word = malloc(2);
    word[0] = 0;
    b = x[0];
    while (str[b] && !ft_isspace(str[b]) && not_3(str[b]))
    {
        if ((str[b] != '"' && str[b] != '\'') && str[b] != '$')
           word = _remallc(word, str[b]);
        if(str[b] == '$')
        {
            join = take_expand_word(str, &b, env);
            word = ft_strjoin(word, join);
        }
        if ((str[b] == '"' || str[b] == '\'') )
        {
            flag = str[b];
            join = quts(str, &b, env);
            word = ft_strjoin(word, join);
            printf("%s\n", word);
        }
        if(!str[b])
            break;
        b++;
    }
    (*x) = b;
    insert(res, word, "CMD", 0);
}
