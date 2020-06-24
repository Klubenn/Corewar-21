/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnrdup.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtristan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 14:58:13 by gtristan          #+#    #+#             */
/*   Updated: 2019/09/24 15:08:07 by gtristan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnrdup(const char *s1, size_t n)
{
	char	*c;
	size_t	j;
	size_t	i;

	i = 0;
	j = ft_strlen(s1) - n;
	if (j == 0)
		return (NULL);
	c = (char *)malloc(sizeof(char) * (j + 1));
	if (!c)
		return (NULL);
	while (s1[n + i])
	{
		c[i] = s1[n + i];
		i++;
	}
	c[i] = '\0';
	return (c);
}
