/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtapioca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/11 11:59:44 by gtristan          #+#    #+#             */
/*   Updated: 2020/07/24 22:54:18 by gtapioca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*snew;
	char	*sold;
	size_t	i;

	i = 0;
	if (!s)
		return (NULL);
	sold = (char *)s;
	snew = (char *)malloc(sizeof(char) * (len + 1));
	if (!snew || (len + 1 == 0))
		return (NULL);
	while (i < len && sold[start + i])
	{
		snew[i] = sold[start + i];
		i++;
	}
	snew[i] = '\0';
	return (snew);
}
