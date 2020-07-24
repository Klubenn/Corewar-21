/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtapioca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/04 20:29:29 by gtapioca          #+#    #+#             */
/*   Updated: 2020/07/24 14:38:58 by gtapioca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"
#include <stdlib.h>

char	*ft_strdup(const char *src)
{
	char	*src1;
	int		i;
	int		j;

	j = 0;
	while (src[j])
		++j;
	++j;
	src1 = (char*)malloc(sizeof(char) * j);
	if (!src1)
		return (0);
	i = 0;
	while (i < j)
	{
		src1[i] = src[i];
		++i;
	}
	return (src1);
}
