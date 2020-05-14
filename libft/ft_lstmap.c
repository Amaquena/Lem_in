/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaquena <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 15:41:59 by amaquena          #+#    #+#             */
/*   Updated: 2019/06/13 16:53:52 by amaquena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list *temp;
	t_list *new;

	if (!lst)
		return (NULL);
	temp = (*f)(lst);
	new = temp;
	while (lst->next)
	{
		lst = lst->next;
		if (!(temp->next = (*f)(lst)))
		{
			free(temp);
			return (NULL);
		}
		temp = temp->next;
	}
	return (new);
}
