/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaquena <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/24 09:21:53 by amaquena          #+#    #+#             */
/*   Updated: 2019/06/13 16:26:50 by amaquena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_atoi(const char *str)
{
	size_t	i;
	int		sign;
	int		val;

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
