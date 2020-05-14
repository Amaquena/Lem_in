/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaquena <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 16:18:16 by amaquena          #+#    #+#             */
/*   Updated: 2019/06/10 16:56:35 by amaquena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa(int n)
{
	char	*num;
	int		i;
	int		numlen;

	if (n == INT_MIN)
		return (ft_strdup("-2147483648"));
	numlen = ft_numlen(n);
	if (!(num = ft_strnew(numlen)))
		return (NULL);
	i = 0;
	if (n < 0)
	{
		num[i++] = '-';
		n *= -1;
	}
	num[numlen--] = '\0';
	if (n > 0)
		while (numlen > 0)
		{
			num[numlen--] = (n % 10) + '0';
			n /= 10;
		}
	if (num[numlen] != '-')
		num[numlen] = (n % 10) + '0';
	return (num);
}
