/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtristan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/11 10:21:48 by gtristan          #+#    #+#             */
/*   Updated: 2019/09/11 14:57:45 by gtristan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	size_t	i;
	size_t	j;
	char	*snew;
	char	*sold;

	i = 0;
	j = 0;
	if (s == NULL)
		return (NULL);
	while (s[i])
		i++;
	sold = (char *)s;
	snew = (char *)malloc(sizeof(char) * (i + 1));
	if (!snew || (i + 1 == 0))
		return (NULL);
	while (j < i)
	{
		snew[j] = f(sold[j]);
		j++;
	}
	snew[j] = '\0';
	return (snew);
}
