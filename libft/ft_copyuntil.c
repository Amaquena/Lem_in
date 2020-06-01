/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_copyuntil.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krissyleemc <krissyleemc@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/30 20:26:48 by krissyleemc       #+#    #+#             */
/*   Updated: 2020/05/30 20:27:10 by krissyleemc      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int ft_copyuntil(char **dst, char *src, char c)
{
    int i;
    int count;
    int pos;

    i = -1;
    count = 0;
    while (src[++i])
        if (src[i] == c)
            break;
    pos = i;
    if (!(*dst = ft_strnew(i)))
        return (0);
    while (src[count] && count < i)
    {
        if (!(*dst = ft_strjoinch(*dst, src[count])))
            return (0);
        count++;
    }
    return (pos);
}
