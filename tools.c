#include "minishell.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	if(s1 == NULL || s2 == NULL)
		return 0;
	while(s1[i] || s2[i])
	{
		if (s1[i] > s2[i] || s1[i] < s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (0);
}

// int	ft_cmp(const char *s1, const char *s2)
// {
// 	size_t			i;
// 	int				flag;
// 	unsigned char	*str1;
// 	unsigned char	*str2;

// 	i = 0;
// 	flag = 0;
// 	str1 = (unsigned char *)s1;
// 	str2 = (unsigned char *)s2;
// 	if ((ft_strlen(s1) > ft_strlen(s2)) || (ft_strlen(s1) < ft_strlen(s2)))
// 		return (-1);
// 	while (str1[i] != '\0' || str2[i] != '\0')
// 	{
// 		if (str1[i] != str2[i])
// 			flag = -1;
// 		i++;
// 	}
// 	return (flag);
// }

