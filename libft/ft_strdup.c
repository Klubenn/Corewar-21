/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtristan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 15:41:43 by gtristan          #+#    #+#             */
/*   Updated: 2019/09/05 17:13:37 by gtristan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*c;
	size_t	i;
	size_t	j;

	i = ft_strlen(s1);
	j = 0;
	c = (char *)malloc(sizeof(char) * (i + 1));
	if (!c || (i + 1 == 0))
		return (NULL);
	while (j < i + 1)
	{
		c[j] = s1[j];
		j++;
	}
	return (c);
}
