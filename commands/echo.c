#include "../minishell.h"

int	echo(char **opt)
{
	char	*str;
	int		i;

	str = NULL;
	if (!opt[1])
		printf("\n");
	else if (ft_strcmp(opt[1], "-n") == 0)
		return (0);
	else if (ft_strcmp(opt[1], "-n") == 0)
	{
		i = 2;
		while(opt[i])
		{
			str = ft_strjoin(str, opt[i]);
			i++;
		}
		printf("%s", str);
	}
	else
	{
		i = 1;
		while(opt[i])
		{
			str = ft_strjoin(str, opt[i]);
			i++;
		}
		printf("%s\n", str);
	}
	return (0);
}