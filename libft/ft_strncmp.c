/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtapioca <gtapioca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/04 20:29:29 by gtapioca          #+#    #+#             */
/*   Updated: 2019/09/18 22:21:09 by gtapioca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*l;
	unsigned char	*k;

	l = (unsigned char *)s1;
	k = (unsigned char *)s2;
	i = 0;
	if (n == 0)
		return (0);
	while (l[i] == k[i] && l[i] && k[i] && i < (n - 1))
		++i;
	return (l[i] - k[i]);
}
