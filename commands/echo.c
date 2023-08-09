#include "../minishell.h"



int	echo(char **opt)
{
	char	*str;
	int		i;
	int		d;
	int		flag;

	str = NULL;
	i = 1;
	d = 0;
	flag = 0;
	if (!opt[1])
	{
		printf("\n");
		return (0);
	}
	while (opt[i] && ft_strcmp(opt[i], "-n") == 0)
	{
		i++;
		flag = 1;
	}
	while(opt[i])
	{
		while(opt[i][d])
		{
			write(1, &opt[i][d], 1);
			d++;
		}
		d = 0;
		i++;
		if (opt[i])
			write(1, " ", 1);
	}
	if (flag == 0)
		write(1, "\n", 1);
	return (0);
}