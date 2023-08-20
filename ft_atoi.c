#include "minishell.h"

// static int	ft_isoverflow(int sign)
// {
// 	if (sign == -1)
// 		return (0);
// 	else
// 		return (-1);
// }

size_t	ft_atoi(const char *str)
{
	size_t		i;
	unsigned long long	result;
	unsigned long long	prev;
	int			sign;

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
		i++;
	}
	printf("atoi %llu\n", result * sign);
	printf("atoisign %d\n", sign);
	if (result > (9223372036854775807ULL + 1))
		return(-1);
	return (result * sign);
}