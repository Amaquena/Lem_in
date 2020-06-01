/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen_chr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krissyleemc <krissyleemc@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/30 21:18:20 by krissyleemc       #+#    #+#             */
/*   Updated: 2020/05/30 21:18:34 by krissyleemc      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int ft_strlen_chr(char *str, char c)
{
    int i;

    i = 0;
    while (str[i] != '\0' && str[i] != c)
        i++;
    return (i);
}
