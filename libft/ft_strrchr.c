/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtristan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/07 16:34:02 by gtristan          #+#    #+#             */
/*   Updated: 2019/09/11 14:59:27 by gtristan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	c1;
	char	*c2;
	int		i;

	i = 0;
	c1 = (char)c;
	c2 = (char*)s;
	while (*c2)
	{
		c2++;
		i++;
	}
	while (*c2 != c1 && (--i >= 0))
		c2--;
	if (*c2 == c1)
		return (c2);
	else
		return (NULL);
}
