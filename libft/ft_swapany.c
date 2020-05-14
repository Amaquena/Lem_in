/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_swapany.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaquena <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 10:26:48 by amaquena          #+#    #+#             */
/*   Updated: 2019/09/19 12:44:47 by amaquena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_swapany(void *a, void *b, size_t s)
{
	void *temp;

	temp = (void *)malloc(s);
	ft_memcpy(temp, a, s);
	ft_memcpy(a, b, s);
	ft_memcpy(b, temp, s);
	free(temp);
}
