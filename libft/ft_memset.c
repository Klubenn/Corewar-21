/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtristan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/04 14:35:50 by gtristan          #+#    #+#             */
/*   Updated: 2019/09/10 09:52:53 by gtristan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*u;
	unsigned char	p;
	size_t			i;

	u = (unsigned char *)b;
	p = (unsigned char)c;
	i = 0;
	while (i < len)
	{
		u[i] = p;
		i++;
	}
	return (b);
}
