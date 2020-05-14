/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaquena <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 10:45:37 by amaquena          #+#    #+#             */
/*   Updated: 2019/06/10 16:19:35 by amaquena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char	*chrdst;
	char	*chrsrc;
	size_t	n;

	if (dst == NULL && src == NULL)
		return (NULL);
	chrdst = (char *)dst;
	chrsrc = (char *)src;
	n = len;
	if (dst > src)
		while (n-- > 0)
			chrdst[n] = chrsrc[n];
	else
		while (len > 0)
		{
			*chrdst = *chrsrc;
			chrdst++;
			chrsrc++;
			len--;
		}
	return (dst);
}
