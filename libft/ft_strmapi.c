/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaquena <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/30 15:36:04 by amaquena          #+#    #+#             */
/*   Updated: 2019/06/10 16:28:51 by amaquena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	char			*strmem;
	char			*strs;
	char			*memres;

	if (!s || !(memres = ft_memalloc((size_t)ft_strlen((char*)s) + 1)))
		return (NULL);
	strs = (char *)s;
	strmem = memres;
	i = 0;
	while (strs && *strs)
	{
		*strmem = (*f)(i, *strs);
		strs++;
		strmem++;
		i++;
	}
	return (memres);
}
