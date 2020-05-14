/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaquena <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/31 13:11:42 by amaquena          #+#    #+#             */
/*   Updated: 2019/06/10 16:29:53 by amaquena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(const char *s1, const char *s2)
{
	char	*str;

	if ((!s1 || !s2) || !(str = ft_strnew(ft_strlen(s1) + ft_strlen(s2))))
		return (NULL);
	str = ft_strcpy(str, s1);
	if (!(str = ft_strcat((char *)str, (char *)s2)))
		return (NULL);
	else
		return (str);
}
