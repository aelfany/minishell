#include "minishell.h"



void	ft_putstr_fd(char *str, int fd)
{
	int	i;

	i = 0;
	while(str[i])
	{
		write(fd, &str[i], 1);
		i++;
	}
}

int	ft_strlen_delim(char *str, char delim)
{
	int	i;

	i = 0;
	while (str[i] != delim && str[i])
		i++;
	return (i);
}

// int	ft_strcmp(char *s1, char *s2)
// {
// 	int	i;

// 	i = 0;
// 	if(s1 == NULL || s2 == NULL)
// 		return -1;
// 	while (s1[i] || s2[i])
// 	{
// 		if (s1[i] > s2[i] || s1[i] < s2[i])
// 			return (s1[i] - s2[i]);
// 		i++;
// 	}
// 	return (0);
// }

int	calc_size(char *str, char delim)
{
	int	i;
	int	d;

	i = 0;
	d = 0;
	while (str[i])
	{
		if (str[i] == '+')
			d = 1;
		if (str[i] == delim)
			return (i);
		i++;
	}
	i = i - d;
	return (i);
}
