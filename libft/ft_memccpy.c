/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaquena <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 15:15:52 by amaquena          #+#    #+#             */
/*   Updated: 2019/06/03 16:11:51 by amaquena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char *chrdst;
	unsigned char *chrsrc;

	chrdst = (unsigned char *)dst;
	chrsrc = (unsigned char *)src;
	while (n > 0)
	{
		*chrdst = *chrsrc;
		if (*chrsrc == (unsigned char)c)
			return (++chrdst);
		chrdst++;
		chrsrc++;
		n--;
	}
	return (NULL);
}
