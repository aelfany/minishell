/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_gen.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelfany <abelfany@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 16:42:58 by abelfany          #+#    #+#             */
/*   Updated: 2023/07/17 17:09:23 by abelfany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
void error_case(int status)
{
    if(status == 0)
        printf("bash: syntax error");
    exit(10);
}

t_env *creat_list(char *str)
{
    
}