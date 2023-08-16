/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelfany <abelfany@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 22:34:23 by abelfany          #+#    #+#             */
/*   Updated: 2023/08/16 06:44:18 by abelfany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int check_expand_cases(char *str, int x)
{
    
    if (str[x] == '$' && str[x + 1] == '*')
        return (1);
    return 0;
}


char *expand(t_env *env, int count, char *word)
{
    int a;

    a = -1;
    while (env)
    {
        if (!ft_strcmp(env -> opt, word))
        {
            if (count % 2)
            {
                word = malloc(2);
                word[0] = 0;
                while (env -> envr[++a])
                    word = _remallc(word, env -> envr[a]);
            }
            return (word);
        }
        env = env -> next;
    }
    if (env == NULL && count % 2)
        word[0] = 0;
    return (word);
}

void error_hh(char *str)
{
    ft_putstr_fd(str, 2);
    exit(0);
}

char *check_expand_rd(char *str, int *x, t_env *env)
{
    int a;
    char *word;
    int count;
    
    word = malloc(2);
    word[0] = 0;
    count = 0;
    a = x[0] - 1;
    while (str[++a] == '$')
        count++;
    // if (check_expand_cases(str, a-1))
    //     error_hh("Error: $*: ambiguous redirect\n");
    a--;
    while (str[++a] && !ft_isspace(str[a]) && not(str[a]))
        word = _remallc(word, str[a]);
    word = expand(env, count, word);
    (*x) = a;
    return word;
}

// creat function check
// char *rmalloc(char *str, int len, int add)
// {
//     char *re;

//     while(str)
//     {
        
//     }
// }

long long deff(long long a, long long b)
{
    if (a > b)
        return (a - b);
    return (b - a);
}

char *expand_inside_dq(char *str, int *x, t_env *env)
{
    int a;
    int b;
    int y;
    int count;

    a = x[0] - 1;
    count = 0;
    while (str[++a] == '$')
        count++;
    b = ft_strlen(env -> envr);
    y = ft_strlen(str);
    y = deff(b, y);
    return (str);
}

char *take_expand_word(char *str, int *x, t_env *env)
{
    int b;
    char *word;
    int count;
    static int lenght;

    word = malloc(2);
    word[0] = 0;
    count = 0;
    b = x[0] - 1;
    while(str[++b] == '$')
        count++;
    while (str[b] && not(str[b]))
    {
        lenght++;
        word = _remallc(word, str[b++]);
    }
    word = expand(env, count, word);
    (*x) = b;
    return word;
}

int is_yes(char c)
{
    if(c == '|' || c == '<' || c == '>' || ft_isspace(c))
        return (1);
    return (0);
}

char *quots_expand(char *str, int *x)
{
    int b = x[0];
    char flag;
    char *word;
    char *join;
    
    flag = '\'';
    if (str[b] == '"')
        flag = '"';
    word = malloc(2);
    word[0] = 0;
    while (str[b] && !ft_isspace(str[b]))
    {
        if(str[b] == '"' || str[b] == '\'')
        {
            join = quts(str, &b);
            word = ft_strjoin(word, join);
        }
        if(!str[b] || !not_2(str[b]))
            break ;
        b++;
    }
    (*x) = b;
    return word;
}

void check_expand(char *str, int *x, t_creat **res, t_env *env)
{
    int a;
    char *word;
    char *join;

    a = 0;
    while(str[a])
    {
        if(is_yes(str[a]))
            break;
        if(str[a] == '"' || str[a] == '\'')
        {
            join = quots_expand(str, &a);
            word = ft_strjoin(word, join);
        }
        if(str[a] == '$')
        {
            join = take_expand_word(str, &a, env);
            word = ft_strjoin(word, join);
        }
    }
    (*x) = a;
    insert(res, word, "CMD");
}
// c == '\'' || c == '"'
// char	*ff_ft(char *s1, char const *s2)
// {
// 	size_t	i;
// 	size_t	lenres;
// 	char	*alloc;
//     free(s1);

// 	if (!s2)
// 		return (0);
// 	i = 0;
//     s1[0] = 0;
// 	lenres = ft_strlen(s1);
// 	alloc = (char *)malloc(sizeof(char) * (lenres + ft_strlen(s2) + 1));
// 	if (!alloc)
// 		return (0);
// 	while (i < lenres && s1[i] != '\0')
// 	{
// 		alloc[i] = s1[i];
// 		i++;
// 	}
// 	i = 0;
// 	while (i <= lenres && s2[i] != '\0')
// 	{
// 			alloc[lenres] = s2[i];
// 			lenres++;
// 			i++;
// 	}
// 	alloc[lenres] = '\0';
// 	return (alloc);
// }