/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_expand.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelfany <abelfany@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 14:19:37 by abelfany          #+#    #+#             */
/*   Updated: 2023/08/09 20:43:06 by abelfany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
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
void check_rederction(char *str, int *x, t_creat **res, char c)
{
    int b;
    char *word;

    b = x[0];
    word = malloc(2);
    word[0] = 0;
    b = x[0];
    b = b + skip_space(str+b+1)+1;
    while (!ft_isspace(str[b]) && str[b] && not(str[b]))
    {
        word = _remallc(word, str[b]);
        b++;
    }
    (*x) = b;
    if (c == '>')
        insert(res, word, "RDOUT");
    else
        insert(res, word, "RDIN");
}

void rederction_apn(char *str, int *x, t_creat **res)
{
    int b;
    char *word;

    b = x[0];
    word = malloc(2);
    word[0] = 0;
    b = x[0] + 2;
    while(ft_isspace(str[b]))
        b++;
    while (str[b] && !ft_isspace(str[b]) && not(str[b]))
    {
        word = _remallc(word, str[b]);
        b++;
    }
    (*x) = b;
    insert(res, word, "RD_AP");
}

void check_expand(char *str, int *x, t_creat **res)
{
    int b;
    int a;
    int count;

    (void)res;
    count = 0;
    a = 0;
    while(str[a] == '$')
        count++;
    b = x[0];
    a = -1;
    while(str[++a])
        if(str[a] == '$')
            count++;

}