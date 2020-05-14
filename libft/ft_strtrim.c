/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaquena <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/31 13:44:03 by amaquena          #+#    #+#             */
/*   Updated: 2019/06/18 12:29:53 by amaquena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(const char *s)
{
	int		end;
	int		start;
	int		n;
	char	*str;

	if (!s)
		return (NULL);
	start = 0;
	while (ft_isspace(s[start]))
	{
		if (s[start++] == '\0')
			return (ft_strdup(""));
	}
	end = ft_strlen(s) - 1;
	while (ft_isspace(s[end]))
		end--;
	if (!(str = ft_strnew(end - start + 1)))
		return (ft_strdup(""));
	n = 0;
	while (start < end + 1)
		str[n++] = s[start++];
	str[n] = '\0';
	if (!(str))
		return (NULL);
	return (str);
}
