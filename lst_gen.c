/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_gen.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelfany <abelfany@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 16:42:58 by abelfany          #+#    #+#             */
/*   Updated: 2023/08/12 17:35:49 by abelfany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
// void error_case(int status)
// {
//     if(status == 0)
//         printf("bash: syntax error");
//     exit(10);
// }

// void insert_opt(t_creat **root, char *str)
// {
//     int a;
// 	int count;
//     int b;

//     a = 0;
//     b = -1;
// 	count = 0;
//     char **save;
//     while((*root) -> opt[count])
//         count++;
// 	printf("->>> %d\n", count);
// 	save = malloc((count+1) * sizeof(char *));
// 	save[count] = NULL;
// 	a = -1;
// 	while((*root) -> opt[++a])
// 		save[a] = (*root)-> opt[a];
// 	ft_free((*root) -> opt);
// 	a = -1;
//     (*root) -> opt = malloc((count+2) * sizeof(char *));
//     (*root) -> opt[count] = ft_strdup(str);
//     (*root) -> opt[count+1] = NULL;
//     a = 0;
//     while(save[a])
// 	{
//         (*root)-> opt[a] = save[a];	
// 		a++;
// 	}
// 	ft_free(save);
// }
// void	test(t_creat **root, char *item, char *str)
// {
// 	t_creat	*temp;
// 	t_creat	*ptr;

//     temp = NULL;
// 	temp = malloc(sizeof(t_creat));
// 	if (!temp)
// 		exit(0);
//     temp -> cmd = ft_strdup(item);
// 	temp -> token = str;
// 	temp -> opt = malloc(1 * sizeof(char *));
// 	temp -> opt[0] = NULL;
// 	temp -> next = NULL;
// 	if (*root == NULL)
// 		*root = temp;
// 	else
// 	{
// 		ptr = *root;
// 		while (ptr -> next != NULL)
// 			ptr = ptr-> next;
// 		ptr -> next = temp;
// 	}
// }
// int cmp(t_creat *cmp, char *str)
// {
// 	while(cmp)
// 	{
// 		if(ft_strcmp(cmp -> token, "HRD"))
// 			return (1);
// 		if(ft_strcmp(cmp -> token, "RDOUT"))
// 			return (1);
// 		if(ft_strcmp(cmp -> token, "RDIN"))
// 			return (1);
// 		if(ft_strcmp(cmp -> token, "RD_AP"))
// 			return (1);
// 		if(ft_strcmp(cmp -> token, "RD_AP"))
// 			return (1);
// 		if(ft_strcmp(cmp -> token, "PIP"))
// 			return (1);
// 	}
// 	return (0);
// }
int	ft_lenstrs(char **strs)
{
	int	x;

	x = 0;
	while (strs[x])
		x++;
	return (x);
}

int	ft_free(char **strs)
{
	int	x;

	x = 0;
	while (strs[x])
		free(strs[x++]);
	free(strs);
	return (0);
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

t_creat	*ft_lstnew(int x)
{
	t_creat	*hel;
	hel = malloc(sizeof(t_creat));
	if (!hel)
		return (0);
	hel -> opt = malloc((x+1) * sizeof(char *));
	hel -> cmd = ft_strdup("ii");
	hel -> token = ft_strdup("ii");
	hel -> opt[x] = NULL;
	hel -> next = NULL;
	return (hel);
}

t_creat *new_list(t_creat *res, int x)
{
	int a;
	int b;
	t_creat *list;
	list = ft_lstnew(x);
	a = 0;
	b = 1;
	while(res)
	{
		if(!ft_strcmp(res -> token, "CMD") ||
			!ft_strcmp(res -> token, "DQ") ||
			!ft_strcmp(res -> token, "SQ"))
		{
			if(b)
			{
				list -> cmd = ft_strdup(res -> cmd);
				list -> token = ft_strdup(res -> token);
				b--;
			}
			list -> opt[a] = ft_strdup(res -> cmd);
			a++;
		}
		if(list -> opt[a] == NULL)
			break ;
		res = res -> next;
	}
	return list;
}

// t_creat *append_helper(t_creat **tok, t_creat *res)
// {
// 	int count;
// 	t_creat *list;
// 	t_creat *tok;

// 	count = 0;
// 	list = (*tok);
// 	tok = NULL;
// 	while(tok)
// 	{
// 		if(!ft_strcmp((*tok) -> token, "CMD") ||
// 			!ft_strcmp((*tok) -> token, "DQ") || 
// 				!ft_strcmp((*tok) -> token, "SQ"))
// 			count++;
// 		(*tok) = (*tok) -> next;
// 	}
// 	tok = new_list(list, count);
// 	(*tok) = list;
// 	while((*tok))
// 	{
// 		if(ft_strcmp((*tok) -> token, "CMD") 
// 		&& ft_strcmp((*tok) -> token, "DQ") 
// 		&& ft_strcmp((*tok) -> token, "SP")
// 		&& ft_strcmp((*tok) -> token, "SQ"))
// 			insert(&tok, (*tok) -> cmd, (*tok) -> token);
// 		(*tok) = (*tok) -> next;
// 	}
// 	return tok;
// }

t_creat *append(t_creat *res)
{
	int count;
	t_creat *list;
	t_creat *tok;

	count = 0;
	list = res;
	tok = NULL;
	while(res)
	{
		if(!ft_strcmp(res -> token, "CMD") ||
			!ft_strcmp(res -> token, "DQ") || 
				!ft_strcmp(res -> token, "SQ"))
			count++;
		res = res -> next;
	}
	tok = new_list(list, count);
	res = list;
	while(res)
	{
		if(ft_strcmp(res -> token, "CMD") 
		&& ft_strcmp(res -> token, "DQ") 
		&& ft_strcmp(res -> token, "SP")
		&& ft_strcmp(res -> token, "SQ"))
			insert(&tok, res -> cmd, res -> token);
		res = res -> next;
	}
	return tok;
}

// t_creat *append(t_creat *res)
// {
	
// }

// CMD = COMMOND OR WORD
// SQ = SINGLE QUOTS
// DQ = DOUBLE QUOTS
// HRD = NORMAL DELEMITER
// HRD_SQ = HEREDOC DELEMITER WITH DOUBLE QUOTS 
// HRD_DQ = HEREDOC DELEMITER WITH SINGLE QUOTS
