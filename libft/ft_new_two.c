/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_new_two.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtristan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/07 19:09:00 by gtristan          #+#    #+#             */
/*   Updated: 2019/09/11 14:26:33 by gtristan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_two	*ft_new_two(int num, t_two *prev, t_two *next)
{
	t_two *list;

	list = (t_two *)malloc(sizeof(t_two));
	ft_bzero(list, sizeof(t_two));
	list->num = num;
	list->next = next;
	list->prev = prev;
	return (list);
}
