/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelfany <abelfany@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 14:20:31 by abelfany          #+#    #+#             */
/*   Updated: 2023/08/08 17:55:21 by abelfany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int counter_quots(char *str)
{
    int singl_quot;
    int double_quot;

    singl_quot = 0;
    double_quot = 0;
    while (*str)
    {
        if (*str == '"')
            double_quot++;
        if (*str == '\'')
            singl_quot++;
        str++;
    }
    if (singl_quot % 2 != 0 || double_quot % 2 != 0)
        return (1);
    return (0);
}
int not(char c)
{
    if(c == '\'' || c == '"' || c == '<' 
        || c == '>' || c == '$' || ft_isspace(c))
        return (0);
    return (1);
}

void check_heredoc(char *str, int *x, t_creat **res)
{
    int b;
    char *word;

    b = x[0];
    word = malloc(2);
    word[0] = 0;
    b = x[0];
    while(ft_isspace(str[b]))
        b++;
    while (str[b] && !ft_isspace(str[b]))
    {
        if(str[b] == '<' || str[b] == '>')
            printf("syntax error !\n");
        word = _remallc(word, str[b]);
        b++;
    }
    (*x) = b;
    insert(res, word, "\033[0;32mHRD\033[0m");
}

t_creat *read_string(char *str)
{
    t_creat *res;
    int count;
    int x;

    count = 0;
    res = NULL;
    x = skip_w_space(str);
    while (str[x])
    {
        if (counter_quots(str))
        {
            puts("unclosed quots");
            break ;
        }
        if (not(str[x]))
            take_string(str, &x, &res);
        if (!counter_quots(str) && (str[x] == '\'' || str[x] == '"'))
            who_first(str, &x, &res);
        printf("-> %c\n", str[x]);
        if (str[x] == '<' && str[x + 1] == '<')
            check_heredoc(str, &x+2, &res);
        // if (str[x] == '>' || str[x + 1] == '>')
        if (str[x] == '>')
            check_rederction(str, &x, &res, '>');
        if (str[x] == '<')
            check_rederction(str, &x, &res, '<');
        if(ft_isspace(str[x]))
        {
            x += skip_w_space(str+x) - 1;
            insert(&res, " ", "\033[0;32mSP\033[0m");
        }
        if(!str[x])
            break;
        x++;
    }
    return (res);
}

