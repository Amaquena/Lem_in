/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaquena <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/27 13:48:27 by amaquena          #+#    #+#             */
/*   Updated: 2019/05/27 17:00:42 by amaquena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	int		i;
	size_t	needlelen;

	if (*needle == '\0')
		return ((char *)haystack);
	i = 0;
	needlelen = ft_strlen(needle);
	while ((haystack[i] != '\0') && ((needlelen + i) <= len))
	{
		if (ft_strncmp(haystack + i, needle, needlelen) == 0)
			return ((char *)haystack + i);
		i++;
	}
	return (NULL);
}
