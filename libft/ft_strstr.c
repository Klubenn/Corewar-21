/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtristan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/07 16:39:56 by gtristan          #+#    #+#             */
/*   Updated: 2019/09/07 18:52:01 by gtristan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *haystack, const char *needle)
{
	size_t	i;
	char	*h;

	i = ft_strlen(needle);
	h = (char*)haystack;
	if (i == 0)
		return (h);
	while (*h && ft_strncmp(h, needle, i) != 0)
		h++;
	if (ft_strncmp(h, needle, i) == 0)
		return (h);
	return (NULL);
}
