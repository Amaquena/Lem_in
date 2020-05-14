/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaquena <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/31 12:13:18 by amaquena          #+#    #+#             */
/*   Updated: 2019/05/31 12:58:03 by amaquena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(const char *s, unsigned int start, size_t len)
{
	char *str;

	if (!s || !(str = ft_strnew(len)))
		return (NULL);
	str = ft_strncpy(str, s + start, len);
	return (str);
}
