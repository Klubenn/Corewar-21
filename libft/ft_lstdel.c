/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtristan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/13 11:47:16 by gtristan          #+#    #+#             */
/*   Updated: 2019/09/13 12:21:16 by gtristan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void*, size_t))
{
	t_list *b;

	if (alst == NULL || del == NULL)
		return ;
	while ((*alst))
	{
		del((*alst)->content, (*alst)->content_size);
		b = (*alst)->next;
		free(*alst);
		*alst = NULL;
		*alst = b;
	}
}
