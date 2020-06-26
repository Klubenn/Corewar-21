/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtristan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/06 19:27:06 by gtristan          #+#    #+#             */
/*   Updated: 2019/09/10 12:01:24 by gtristan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char c1;
	char *s1;

	c1 = (char)c;
	s1 = (char*)s;
	while (*s1 != c1 && *s1)
		s1++;
	if (*s1 == c1)
		return (s1);
	else
		return (NULL);
}
