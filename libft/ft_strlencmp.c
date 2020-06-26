/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtristan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/07 18:56:36 by gtristan          #+#    #+#             */
/*   Updated: 2019/09/10 13:21:33 by gtristan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strlencmp(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	char	*h;
	char	*n;

	i = ft_strlen(needle);
	h = (char*)haystack;
	n = (char*)needle;
	if (i == 0)
		return (h);
	if (i < len - 1)
		return (NULL);
	while (*h && ft_strncmp(h, needle, len) != 0)
		h++;
	if (ft_strncmp(h, needle, len) == 0)
	{
		i = 0;
		while (++i <= len)
		{
			if (*h != *n)
				return (NULL);
		}
		return (h);
	}
	return (NULL);
}
