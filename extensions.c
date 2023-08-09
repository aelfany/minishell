/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extensions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelfany <abelfany@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 15:55:44 by abelfany          #+#    #+#             */
/*   Updated: 2023/08/09 17:50:31 by abelfany         ###   ########.fr       */
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

void error_handler(void)
{
    puts("\033[0;91msyntax error !\033[0m");
}