/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaquena <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 11:08:40 by amaquena          #+#    #+#             */
/*   Updated: 2019/05/28 14:16:45 by amaquena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char *chrdst;
	char *chrsrc;

	if (dst == NULL && src == NULL)
		return (NULL);
	chrdst = (char *)dst;
	chrsrc = (char *)src;
	while (n > 0)
	{
		*chrdst = *chrsrc;
		chrdst++;
		chrsrc++;
		n--;
	}
	return (dst);
}
