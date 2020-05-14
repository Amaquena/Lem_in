/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaquena <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/24 15:34:21 by amaquena          #+#    #+#             */
/*   Updated: 2019/06/10 16:23:19 by amaquena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int				end;
	unsigned char	chr;

	chr = (unsigned char)c;
	end = ft_strlen(s);
	while (s[end] != chr && end > 0)
		end--;
	if (s[end] == chr)
		return ((char *)s + end);
	return (NULL);
}
