/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_countwords.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtristan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/04 16:16:57 by gtristan          #+#    #+#             */
/*   Updated: 2019/09/24 15:07:36 by gtristan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_countwords(char *s)
{
	size_t	j;

	j = 0;
	while (*s)
	{
		if (!ft_isspace(*s))
		{
			j++;
			while (!ft_isspace(*s) && *s)
				s++;
		}
		while (ft_isspace(*s))
			s++;
	}
	return (j);
}
