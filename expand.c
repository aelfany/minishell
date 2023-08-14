/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelfany <abelfany@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 22:34:23 by abelfany          #+#    #+#             */
/*   Updated: 2023/08/14 23:14:06 by abelfany         ###   ########.fr       */
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
    printf("%c %d\n", str[a], a);
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
// char *take_expand_word(char *str, int *x, t_env *env)
// {
//     int b;
//     int count;

//     count = 0;
//     b = x[0] - 1;
//     while(str[++b] == '$')
//         count++;
// }
void check_expand(char *str, int *x, t_creat **res, t_env *env)
{
    int a;
    char *word;
    int count;
    
    word = malloc(2);
    word[0] = 0;
    count = 0;
    a = x[0] - 1;
    while (str[++a] && !ft_isspace(str[a]) && str[a] != '$')
        word = _remallc(word, str[a]);
    word = expand(env, count, word);
    (*x) = a;
    insert(res, word, "CMD");
}