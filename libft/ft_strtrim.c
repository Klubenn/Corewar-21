/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtristan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/11 15:02:42 by gtristan          #+#    #+#             */
/*   Updated: 2019/09/12 18:41:50 by gtristan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isblank(char const s)
{
	if (s == ' ' || s == '\n' || s == '\t')
		return (1);
	return (0);
}

char		*ft_strtrim(char const *s)
{
	char	*str;
	size_t	start;
	size_t	end;
	size_t	i;

	if (!s)
		return (NULL);
	start = 0;
	i = 0;
	end = ft_strlen(s);
	while (ft_isblank(s[start]))
		start++;
	while (end && ft_isblank(s[end]))
		end--;
	if (end < start)
		end = start;
	if (!(str = (char *)ft_memalloc(sizeof(char) *
			(end - start + 2 - (s[end] == '\0')))))
		return (NULL);
	while (i + start <= end)
	{
		str[i] = (char const)s[i + start];
		i++;
	}
	return (str);
}
