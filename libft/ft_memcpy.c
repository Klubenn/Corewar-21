/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memcpy.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtristan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 07:42:52 by gtristan          #+#    #+#             */
/*   Updated: 2019/09/12 17:28:14 by gtristan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *str1, const void *str2, size_t n)
{
	size_t	i;
	char	*s2;
	char	*s1;

	i = 0;
	if (str1 == NULL && str2 == NULL)
		return (NULL);
	s2 = (char*)str2;
	s1 = (char*)str1;
	while (i < n)
	{
		s1[i] = s2[i];
		i++;
	}
	return (str1);
}
