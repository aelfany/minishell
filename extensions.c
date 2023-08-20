/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extensions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelfany <abelfany@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 15:55:44 by abelfany          #+#    #+#             */
/*   Updated: 2023/08/20 03:57:18 by abelfany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int not(char c)
{
    if(c == '\'' || c == '"' || c == '|'||c == '<' 
        || c == '>' || c == '$' || ft_isspace(c))
        return (0);
    return (1);
}

int counter(char *str, char c)
{
    int a;
    int count;

    a = 0;
    count = 0;
    while(str[++a])
        if(str[a] == c)
            count++;
    return (count);
}

void error_handler(char *str)
{
    printf("minishell: syntax error near unexpected token `%s'\n", str);
}