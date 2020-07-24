/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtapioca <gtapioca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 18:44:49 by gtapioca          #+#    #+#             */
/*   Updated: 2019/09/18 22:54:28 by gtapioca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static void	space_skipper(char const *s, int *c)
{
	while (s[c[1]] == ' ' || s[c[1]] == '\t' || s[c[1]] == '\n')
	{
		c[0]--;
		c[1]--;
	}
	c[1]++;
	c[0]++;
}

static int	counter(char const *s)
{
	int c[2];

	c[0] = 0;
	c[1] = 0;
	if (!(*s))
		return (0);
	while (*s)
	{
		if (c[0] == 0)
		{
			while (s[c[1]] == ' ' || s[c[1]] == '\t' || s[c[1]] == '\n')
				c[1]++;
		}
		if (s[c[1]] == '\0')
			break ;
		if (s[c[1] + 1] == '\0')
		{
			space_skipper(s, c);
			break ;
		}
		c[0]++;
		c[1]++;
	}
	return (c[0]);
}

char		*ft_strtrim(char const *s)
{
	char	*ptr;
	int		i;
	int		j;

	if (!s)
		return (0);
	i = counter(s);
	j = 0;
	ptr = (char *)malloc(sizeof(char) * (i + 1));
	if (!ptr)
		return (0);
	while (j < i && i != 0)
	{
		if (j == 0)
		{
			while (*s == ' ' || *s == '\t' || *s == '\n')
				s++;
		}
		ptr[j] = *s;
		s++;
		j++;
	}
	ptr[j] = '\0';
	return (ptr);
}
