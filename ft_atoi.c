#include "minishell.h"

static int	ft_isoverflow(int sign)
{
	if (sign == -1)
		return (0);
	else
		return (-1);
}

int	ft_atoi(const char *str)
{
	size_t	i;
	size_t	result;
	size_t	prev;
	int		sign;

	i = 0;
	result = 0;
	sign = 1;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = sign * -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		prev = result;
		result = result * 10 + (str[i] - '0');
		if ((result / 10) != prev)
			return (ft_isoverflow(sign));
		i++;
	}
	return (result * sign);
}