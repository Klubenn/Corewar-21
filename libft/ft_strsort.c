/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtristan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/15 14:05:34 by gtristan          #+#    #+#             */
/*   Updated: 2019/09/15 14:43:21 by gtristan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_strsort(char **str)
{
	int		i;
	int		j;
	int		h;
	char	*s;

	i = 0;
	h = 0;
	while (str[h])
		h++;
	while (i < 5)
	{
		j = 0;
		while (j < 5 - 1)
		{
			if (ft_strcmp(str[j], str[j + 1]) > 0)
			{
				s = str[j];
				str[j] = str[j + 1];
				str[j + 1] = s;
			}
			j++;
		}
		i++;
	}
}
