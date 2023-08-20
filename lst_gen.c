/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_gen.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelfany <abelfany@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 16:42:58 by abelfany          #+#    #+#             */
/*   Updated: 2023/08/20 03:48:46 by abelfany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	insert(t_creat **root, char *item, char *str, int flag)
{
	t_creat	*temp;
	t_creat	*ptr;

	flag = 0;
	temp = NULL;
	temp = malloc(sizeof(t_creat));
	if (!temp)
		exit(0);
	temp -> cmd = item;
	temp -> token = ft_strdup(str);
	temp -> opt = NULL;
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

t_creat	*ft_lstnew(char **str)
{
	t_creat	*hel;

	hel = malloc(sizeof(t_creat));
	if (!hel)
		return (0);
	hel -> cmd = str[0];
	hel -> opt = str;
	hel -> token = ft_strdup("CMD");
	hel -> next = NULL;
	return (hel);
}

int	lenlist(t_creat *list)
{
	int	x;

	x = 0;
	while (list && ft_strcmp(list-> token, "PIP"))
	{
		if (!ft_strcmp(list -> token, "CMD"))
			x++;
		list = list -> next;
	}
	return (x);
}

t_creat	*cmd_node(t_creat *res)
{
	int		a;
	char	**opt;
	t_creat	*list;

	list = NULL;
	a = lenlist(res);
	opt = malloc((a + 1) * sizeof(char *));
	opt[a] = NULL;
	a = -1;
	while (res && ft_strcmp(res -> token, "PIP"))
	{
		if (!ft_strcmp(res -> token, "CMD"))
			opt[++a] = ft_strdup(res -> cmd);
		res = res -> next;
	}
	list = ft_lstnew(opt);
	return (list);
}
void free_list(t_creat **save)
{

	while ((*save) -> next)
	{
		free((*save) -> token);
		free((*save) -> cmd);
		free((*save));
		(*save) = (*save) -> next;
	}
}
t_creat	*new_list(t_creat *res)
{
	t_creat	*save;
	t_creat	*list;
	t_creat	*add;

	list = NULL;
	if (check_command(res))
		list = cmd_node(res);
	save = res;
	add = NULL;
	while (save)
	{
		if (ft_strcmp(save -> token, "CMD"))
			insert(&list, save -> cmd, save -> token, 0);
		if (!ft_strcmp(save -> token, "PIP"))
		{
			if (check_command(save -> next))
			{
				add = cmd_node(save -> next);
				ft_lstadd_back(&list, add);
			}
		}
		save = save -> next;
	}
	free_list(&res);
	return (list);
}

// // CMD = COMMOND OR WORD
// // SQ = SINGLE QUOTS
// // DQ = DOUBLE QUOTS
// // HRD = NORMAL DELEMITER
// // HRD_SQ = HEREDOC DELEMITER WITH DOUBLE QUOTS 
// // HRD_DQ = HEREDOC DELEMITER WITH SINGLE QUOTS
