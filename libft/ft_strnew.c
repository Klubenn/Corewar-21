/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtapioca <gtapioca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/04 20:29:29 by gtapioca          #+#    #+#             */
/*   Updated: 2019/09/19 21:10:47 by gtapioca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>

char	*ft_strnew(size_t size)
{
	char		*ptr;
	size_t		i;

	i = 0;
	if (size > (size + 1))
		return (0);
	ptr = (char *)malloc(sizeof(char) * (size + 1));
	if (!ptr)
		return (0);
	while (i <= size)
	{
		ptr[i] = '\0';
		i++;
	}
	if (size != 0)
		ptr[i] = '\0';
	return (ptr);
}
