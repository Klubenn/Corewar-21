/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtristan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/06 16:59:48 by gtristan          #+#    #+#             */
/*   Updated: 2019/09/10 09:53:54 by gtristan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, char *src, size_t size)
{
	size_t i;
	size_t j;

	i = 1;
	if (ft_strlen(dst) <= size)
		j = ft_strlen(src) + ft_strlen(dst);
	else
		j = ft_strlen(src) + size;
	while (*dst && i < size)
	{
		dst++;
		i++;
	}
	if (i < size)
	{
		while (*src && i < size)
		{
			*dst = *src;
			dst++;
			src++;
			i++;
		}
		*dst = '\0';
	}
	return (j);
}
