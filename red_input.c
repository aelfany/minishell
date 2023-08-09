/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelfany <abelfany@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 14:20:31 by abelfany          #+#    #+#             */
/*   Updated: 2023/08/09 21:41:44 by abelfany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int find_last(char *str, int *flag, char c)
{
    int a;

    a = 1;
    int f = 0;
    while(str[a])
    {
        if(str[a] == c)
        {
            f = 1;
            break;
        }
        a++;
    }
    (*flag) = f;
    return a;
}
int counter_quots(char *str)
{
    int b;
    int flag;
    
    b = 0;
    while(str[b])
    {
        if(str[b] == '"' || str[b] == '\'')
        {
            b += find_last(str+b, &flag, str[b]);
            if(flag == 0)
                return 1;
        }
        b++;
    }
    return 0;
}


void check_heredoc(char *str, int *x, t_creat **res)
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
    insert(res, word, "HRD");
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
            take_string(str, &x, &res);
        if (!counter_quots(str) && (str[x] == '\'' || str[x] == '"'))
            who_first(str, &x, &res);
        if (str[x] == '<' && str[x + 1] == '<')
            check_heredoc(str, &x, &res);
        if (str[x] == '>' && str[x + 1] == '>')
            rederction_apn(str, &x, &res);
        if (str[x] == '>')
            check_rederction(str, &x, &res, '>');
        if (str[x] == '<')
            check_rederction(str, &x, &res, '<');
        if (str[x] == '|')
            insert(&res, "|", "PIP");
        if(ft_isspace(str[x]))
        {
            x += skip_w_space(str+x) - 1;
            insert(&res, " ", "SP");
        }
        if(!str[x])
            break;
        if(ft_isspace(str[x]) || str[x] == '$' || str[x] == '|')
            x++;
    }
    return (append(res));
}
        // printf("->>> %c\n", str[x]);
        // printf("->>> %d\n", x);
        // printf("->>> %d %c\n", x, str[x]);