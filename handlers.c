/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelfany <abelfany@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 09:59:47 by abelfany          #+#    #+#             */
/*   Updated: 2023/07/19 14:40:00 by abelfany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
char *_remallc(char *str, char c)
{
    char *save;
    int a;
    
    a = 0;
    save = ft_strcpy(save, str);
    free(str);
    str = malloc((ft_strlen(str)+2) * sizeof(char));
    str[ft_strlen(save)] = c;
    str[ft_strlen(save)+1] = 0;
    while (*save)
    {
        str[a] = *save;
        *save++;
    }
    return (str);
}
int flag_fun(char *str, char x)
{
    while (*str)
    {
        if (*str == x)
            return (1);
        str++;
    }
    return (0);
}
int find_index_last_quot(char *str)
{
    int a;
    int ;

    a = ft_strlen(str) - 1;
    if (str[0] == 34 || str[0] == 39 && str[1] == 0)
        return 1;
    while (str[a] && a)
    {
        if (str[a] == 34 || str[a] == 39)
            return (a);
        a--;
    }
    return (0);
}

int	ft_isascii(int c)
{
    if (c == 34 && c == 39)
	    if (c >= 0 && c <= 127)
		return (1);
	return (0);
}
char *take_every_char(char *str, int start, int end) //end included & start encluded
{
    char *cpy;
    char *word;
    int flag;

    flag = 0;
    while (*str == !ft_isprint(*str))
    {
        if (*str == '\'' || *str == '"')
        {
            if (*str == '\'')
                flag = 1;
            if (*str == '"')
                flag = 2;
            break ;
        }
        str++;
    }
    word = _remallc(str, *str);
    while (*str != '|' && *str)
    {
        if (ft_isascii(*str))
            word = _remallc(word, *str);
    }
}