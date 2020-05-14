#include "libft.h"

long		ft_atol(const char *str)
{
    size_t	i;
	int		sign;
	long	val;

	i = 0;
	if (*str == '\0')
		return (0);
	while (ft_isspace(str[i]))
		i++;
	sign = 1;
	if ((str[i] == '-') || (str[i] == '+'))
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	val = 0;
	while (ft_isdigit(str[i]) && str[i] != '\0')
	{
		val = (val * 10) + (str[i] - '0');
		i++;
	}
	return (sign * val);

}