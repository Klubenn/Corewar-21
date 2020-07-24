/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtristan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/04 16:16:57 by gtristan          #+#    #+#             */
/*   Updated: 2019/09/24 15:07:36 by gtristan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	size_t			i;
	unsigned char	*src1;
	unsigned char	*dst1;
	unsigned char	a;

	if (dst == NULL && src == NULL)
		return (NULL);
	i = 0;
	src1 = (unsigned char *)src;
	dst1 = (unsigned char *)dst;
	a = (unsigned char)c;
	while (i < n)
	{
		dst1[i] = src1[i];
		if (src1[i] == a)
		{
			i++;
			return (&(dst1[i]));
		}
		i++;
	}
	return (NULL);
}
