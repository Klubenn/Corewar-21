/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtapioca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 18:44:49 by gtapioca          #+#    #+#             */
/*   Updated: 2020/07/24 14:38:58 by gtapioca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"
#include <stdlib.h>

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list *ptr;

	ptr = (t_list *)malloc(sizeof(t_list));
	if (ptr == NULL)
		return (0);
	if (content == NULL)
	{
		ptr->content = NULL;
		ptr->content_size = 0;
	}
	else
	{
		ptr->content = (void *)malloc(sizeof(void) * content_size);
		if (!(ptr->content))
			return (0);
		ft_memcpy(ptr->content, content, content_size);
		ptr->content_size = content_size;
	}
	ptr->next = 0;
	return (ptr);
}
