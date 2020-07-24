/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtapioca <gtapioca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 18:44:49 by gtapioca          #+#    #+#             */
/*   Updated: 2019/09/19 17:57:10 by gtapioca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	a;
	unsigned char	*b;

	a = (unsigned char)c;
	b = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		if (*b == a)
			return (b);
		++b;
		++i;
	}
	return (NULL);
}
