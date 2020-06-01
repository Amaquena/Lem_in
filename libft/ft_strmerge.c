/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmerge.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krissyleemc <krissyleemc@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/30 21:14:27 by krissyleemc       #+#    #+#             */
/*   Updated: 2020/05/30 21:14:37 by krissyleemc      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char *ft_strmerge(char *a, char *b)
{
    char *ret;

    ret = ft_strjoin(a, b);
    ft_strdel(&a);
    ft_strdel(&b);
    return (ret);
}
