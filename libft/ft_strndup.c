/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtristan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 15:41:43 by gtristan          #+#    #+#             */
/*   Updated: 2019/09/19 14:49:29 by gtristan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *s1, size_t n)
{
	char	*c;
	size_t	j;

	j = 0;
	c = (char *)malloc(sizeof(char) * (n + 1));
	if (!c || (n + 1 == 0))
		return (NULL);
	while (s1[j] && j < n)
	{
		c[j] = s1[j];
		j++;
	}
	c[j] = '\0';
	return (c);
}
