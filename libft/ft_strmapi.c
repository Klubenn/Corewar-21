/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtapioca <gtapioca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/04 20:29:29 by gtapioca          #+#    #+#             */
/*   Updated: 2019/09/18 22:19:39 by gtapioca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*res;
	unsigned int	i;
	unsigned int	n;

	i = 0;
	n = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	res = (char *)malloc(sizeof(char) * (i + 1));
	if (!res)
		return (0);
	while (n < i)
	{
		res[n] = (*f)(n, s[n]);
		n++;
	}
	if (i != 0)
		res[n] = '\0';
	return (res);
}
