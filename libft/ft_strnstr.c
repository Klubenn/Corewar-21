/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtristan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/07 18:56:36 by gtristan          #+#    #+#             */
/*   Updated: 2019/09/12 18:15:55 by gtristan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;
	char	*h;
	char	*n;

	if (haystack == NULL && needle == NULL)
		return (NULL);
	i = ft_strlen(needle);
	h = (char*)haystack;
	n = (char*)needle;
	if (ft_strlen(haystack) < i || len < i)
		return (NULL);
	if (i == 0)
		return (h);
	j = 0;
	while (h[j] && ft_strncmp(&h[j], n, i) != 0 && j < len - 1 && i <= len - j)
		j++;
	if (ft_strncmp(&h[j], needle, i) == 0)
		return (&h[j]);
	return (NULL);
}
