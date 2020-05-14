/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaquena <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/23 16:46:11 by amaquena          #+#    #+#             */
/*   Updated: 2019/06/13 16:24:17 by amaquena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char *str1;
	unsigned char *str2;

	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	while ((*str1 && *str2) && n && (*str1 == *str2))
	{
		str1++;
		str2++;
		n--;
	}
	if (*str1 < *str2 && n > 0)
		return (-1);
	else if (*str1 > *str2 && n > 0)
		return (1);
	return (0);
}
