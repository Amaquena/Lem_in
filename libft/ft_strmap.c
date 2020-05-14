/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaquena <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/30 13:22:17 by amaquena          #+#    #+#             */
/*   Updated: 2019/06/10 16:28:14 by amaquena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	char *memres;
	char *strs;
	char *strmem;

	if (!s || !(memres = ft_memalloc((size_t)ft_strlen((char*)s) + 1)))
		return (NULL);
	strs = (char *)s;
	strmem = memres;
	while (strs && *strs)
	{
		*strmem = (*f)(*strs);
		strmem++;
		strs++;
	}
	return (memres);
}
