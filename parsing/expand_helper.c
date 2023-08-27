/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelfany <abelfany@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 07:57:17 by abelfany          #+#    #+#             */
/*   Updated: 2023/08/27 06:28:34 by abelfany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_sp_ch(char c)
{
	if (c == '_' || c == '\0' )
		return (0);
	if (!ft_isalpha(c))
		return (1);
	return (0);
}

char	*take_expand_heredoc(char *str, int *x, t_env *env)
{
	int		b;
	int		sv;
	char	*word;
	int		count;

	word = NULL;
	count = 0;
	b = x[0] - 1;
	while (str[++b] == '$')
		count++;
	sv = b;
	if (count % 2 && str[b] == '?')
		word = ft_strjoin_free(word, ft_itoa(g_exitstatus), 1, 1);
	if (count % 2 && str[b] == '%')
		word = _remallc(word, '$');
	else if (word && count % 2 && str[b] && check_sp_ch(str[b]))
		b++;
	while (str[b] && not(str[b]))
		word = _remallc(word, str[b++]);
	if (count % 2 && word == 0)
		return ((*x) = b, word = _remallc(word, '$'));
	if (!check_sp_ch(str[sv]))
		word = expand(env, count, word);
	return ((*x) = b, word);
}

int	not_d(char c)
{
	if (c == '\'' || c == '"' || c == '|' || c == '<' 
		|| c == '>' || c == '$')
		return (0);
	return (1);
}

char	*expand_word_red(char *str, int *x, t_env *env, t_creat **res)
{
	int		b;
	int		sv;
	char	*word;
	int		count;

	word = NULL;
	count = 0;
	b = x[0] - 1;
	while (str[++b] == '$')
		count++;
	sv = b;
	if (count % 2 && str[b] == '?')
		word = ft_strjoin_free(word, ft_itoa(g_exitstatus), 1, 1);
	if (count % 2 && str[b] == '%')
		word = _remallc(word, '$');
	else if (word && count % 2 && str[b] && check_sp_ch(str[b]))
		b++;
	while (str[b] && not_d(str[b]))
		word = _remallc(word, str[b++]);
	if (count % 2 && word == 0)
		return ((*x) = b, word = _remallc(word, '$'));
	if (!check_sp_ch(str[sv]))
		word = expand_red(env, count, word, res);
	return ((*x) = b, word);
}

char	*expand_word(char *str, int *x, t_env *env)
{
	int		b;
	int		sv;
	char	*word;
	int		count;

	word = NULL;
	count = 0;
	b = x[0] - 1;
	while (str[++b] == '$')
		count++;
	sv = b;
	if (count % 2 && str[b] == '?')
		word = ft_strjoin_free(word, ft_itoa(g_exitstatus), 1, 1);
	if (count % 2 && str[b] == '%')
		word = _remallc(word, '$');
	else if (word && count % 2 && str[b] && check_sp_ch(str[b]))
		b++;
	while (str[b] && not(str[b]))
		word = _remallc(word, str[b++]);
	if (count % 2 && word == 0)
		return ((*x) = b, word = _remallc(word, '$'));
	if (!check_sp_ch(str[sv]))
		word = expand(env, count, word);
	return ((*x) = b, word);
}
