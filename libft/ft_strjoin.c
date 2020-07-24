/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtapioca <gtapioca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/04 20:29:29 by gtapioca          #+#    #+#             */
/*   Updated: 2019/09/19 17:29:39 by gtapioca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static char	*word_put(char *ptr, char const *s1, char const *s2, int *c)
{
	int k;

	k = 0;
	while (k < c[0])
	{
		ptr[k] = s1[k];
		k++;
	}
	while (k < c[0] + c[1])
	{
		ptr[k] = s2[k - c[0]];
		k++;
	}
	ptr[k] = '\0';
	return (ptr);
}

static int	count(char const *s)
{
	int i;

	i = 0;
	if (s[i] != '\0')
	{
		while (s[i])
			++i;
	}
	return (i);
}

char		*ft_strjoin(char const *s1, char const *s2)
{
	char	*ptr;
	int		c[2];

	c[0] = 0;
	c[1] = 0;
	if (!s1 && !s2)
		return (0);
	if (s1)
		c[0] = count(s1);
	if (s2)
		c[1] = count(s2);
	ptr = (char *)malloc(sizeof(char) * (c[0] + c[1] + 1));
	if (!ptr)
		return (0);
	return (word_put(ptr, s1, s2, c));
}
