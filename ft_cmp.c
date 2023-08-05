#include "minishell.h"

int	ft_cmp(const char *s1, const char *s2)
{
	size_t			i;
	int				flag;
	unsigned char	*str1;
	unsigned char	*str2;

	i = 0;
	flag = 0;
	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	if ((ft_strlen(s1) > ft_strlen(s2)) || (ft_strlen(s1) < ft_strlen(s2)))
		return (-1);
	while (str1[i] != '\0' || str2[i] != '\0')
	{
		if (str1[i] != str2[i])
			flag = -1;
		i++;
	}
	return (flag);
}