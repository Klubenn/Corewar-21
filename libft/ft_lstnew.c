/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtristan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/13 09:32:59 by gtristan          #+#    #+#             */
/*   Updated: 2019/09/13 15:46:53 by gtristan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list	*a;

	a = (t_list *)malloc(sizeof(t_list));
	if (!a || (content_size == 0))
		return (NULL);
	if (content != NULL)
	{
		if (!(a->content = (void *)malloc(content_size)))
			return (NULL);
		ft_memmove(a->content, content, content_size);
		a->content_size = content_size;
		a->next = NULL;
		return (a);
	}
	else
	{
		a->content = NULL;
		a->content_size = 0;
		a->next = NULL;
		return (a);
	}
}
