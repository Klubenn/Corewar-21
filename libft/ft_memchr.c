/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtristan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 12:17:06 by gtristan          #+#    #+#             */
/*   Updated: 2019/09/05 15:17:44 by gtristan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t	i;
	char	r;
	char	*str;

	i = 0;
	str = (char *)s;
	r = (char)c;
	while (i < n && str[i] != r)
		i++;
	if (i == n)
		return (NULL);
	if (str[i] == r)
		return (str + i);
	return (NULL);
}
