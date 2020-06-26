/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtristan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 11:00:28 by gtristan          #+#    #+#             */
/*   Updated: 2019/09/11 14:55:35 by gtristan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char	*tmpdst;
	char	*tmpsrc;
	int		i;

	i = -1;
	if (dst == NULL && src == NULL)
		return (NULL);
	tmpsrc = (char *)src;
	tmpdst = (char *)dst;
	if (tmpsrc >= tmpdst)
	{
		while (++i < (int)len)
			tmpdst[i] = tmpsrc[i];
	}
	else
	{
		i = len;
		while (--i >= 0)
			tmpdst[i] = tmpsrc[i];
	}
	return (tmpdst);
}
