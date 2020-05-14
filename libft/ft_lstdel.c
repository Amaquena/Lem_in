/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lsdel.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaquena <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 12:00:17 by amaquena          #+#    #+#             */
/*   Updated: 2019/06/11 13:37:42 by amaquena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list	*temp;
	t_list	*current;

	current = (*alst);
	while (current != NULL)
	{
		temp = current->next;
		(*del)(current->content, current->content_size);
		free(current);
		current = temp;
	}
	*alst = NULL;
}
