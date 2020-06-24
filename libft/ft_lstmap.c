/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtristan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/13 13:18:03 by gtristan          #+#    #+#             */
/*   Updated: 2019/09/24 15:07:16 by gtristan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*a;
	t_list	*c;

	if (lst == NULL)
		return (NULL);
	a = f(lst);
	c = a;
	while (lst->next)
	{
		lst = lst->next;
		if (!(a->next = f(lst)))
		{
			a = c;
			while (c)
			{
				c = a->next;
				free(a->content);
				free(a);
				a = c;
			}
			return (NULL);
		}
		a = a->next;
	}
	return (c);
}
