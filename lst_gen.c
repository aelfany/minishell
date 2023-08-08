/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_gen.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelfany <abelfany@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 16:42:58 by abelfany          #+#    #+#             */
/*   Updated: 2023/08/08 14:37:11 by abelfany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
void error_case(int status)
{
    if(status == 0)
        printf("bash: syntax error");
    exit(10);
}

void	insert(t_creat **root, char *item, char *str)
{
	t_creat	*temp;
	t_creat	*ptr;

    temp = NULL;
	temp = malloc(sizeof(t_creat));
	if (!temp)
		exit(0);
    temp -> cmd = ft_strdup(item); 
	temp -> token = str;
	temp -> next = NULL;
	if (*root == NULL)
		*root = temp;
	else
	{
		ptr = *root;
		while (ptr -> next != NULL)
			ptr = ptr-> next;
		ptr -> next = temp;
	}
}
