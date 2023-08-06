/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelfany <abelfany@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 14:20:31 by abelfany          #+#    #+#             */
/*   Updated: 2023/08/06 19:10:42 by abelfany         ###   ########.fr       */
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

t_creat *read_string(char *str)
{
    t_creat *res;
    // char *ins;
    int count;
    int x;

    count = 0;
    res = NULL;
    x = skip_w_space(str);
    while (str[x])
    {
        if (counter_quots(str)){
            puts("unclosed quots");
            break ;
        }
        if (!counter_quots(str) && (str[x] == '\'' || str[x] == '"'))
            who_first(str, &x, &res);
        if (ft_isalpha(str[x]))
            take_string(str, &x, &res);
        if (str[x] == '>')
            check_rederction(str, &x, &res, '>');
        if (str[x] == '<')
            check_rederction(str, &x, &res, '<');
        if(ft_isspace(str[x]))
        {
            x += skip_w_space(str+x);
            insert(&res, " ", "\033[0;32mSP\033[0m");
            printf("%c\n", str[x+1]);
        }
        // if (str[x] == '$')
        //     check_expand(str, &x, &res);
        x++;
        // exit(0);
    }
    return (res);
}
