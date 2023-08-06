/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_and_quots.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelfany <abelfany@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 09:59:47 by abelfany          #+#    #+#             */
/*   Updated: 2023/08/06 19:11:29 by abelfany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *_remallc(char *str, char c)
{
    char *save;
    int a;
    
    a = 0;
    save = malloc(strlen(str)+1);
    while(str[a])
    {
        save[a] = str[a];
        a++;
    }
    save[a] = 0;
    str = malloc((strlen(str)+2) * sizeof(char));
    str[strlen(save)] = c;
    str[strlen(save)+1] = 0;
    a = 0;
    while (save[a])
    {
        str[a] = save[a];
        a++;
    }
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

void who_first(char *str, int *x, t_creat **res)
{
    int b = x[0];
    char flag;
    char *word;
    flag = '\'';
    if (str[b] == '"')
        flag = '"';
    else
    word = malloc(2);
    word[0] = 0;
    b++;
    while (str[b] != flag && str[b])
    {
        if (ft_isascii(str[b]))
            word = _remallc(word, str[b]);
        b++;
    }
    (*x) = b;
    if(flag == '\'')
        insert(res, word, "\033[0;32mSQ\033[0m");
    else 
        insert(res, word, "\033[0;32mDQ\033[0m");
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

void take_string(char *str, int *x, t_creat **res)
{
    int b;
    char *word;

    word = malloc(2);
    word[0] = 0;
    b = x[0];
    while (str[b] && ft_isalpha(str[b]))
    {
        if (ft_isalpha(str[b]))
            word = _remallc(word, str[b]);
        b++;
    }
    (*x) = b;
    // printf("->> %s\n", word);
    insert(res, word, "\033[0;32mCMD\033[0m");
}
