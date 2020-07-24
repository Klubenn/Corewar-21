/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtapioca <gtapioca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/04 20:29:29 by gtapioca          #+#    #+#             */
/*   Updated: 2019/09/18 21:38:27 by gtapioca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

static void	*copypasthelp(void *dst, const void *src, int c)
{
	size_t			i;
	size_t			j;
	unsigned char	*l;

	i = 0;
	j = 0;
	l = 0;
	while (((unsigned char*)src)[i] != ((unsigned char)c))
	{
		((unsigned char*)dst)[i] = ((unsigned char*)src)[i];
		i++;
	}
	((unsigned char*)dst)[i] = ((unsigned char*)src)[i];
	l = (unsigned char *)dst;
	while (j < i)
	{
		l++;
		j++;
	}
	l++;
	return (l);
}

static void	*copipaster2(void *dst, const void *src, size_t n)
{
	size_t i;

	i = 0;
	while (i < n)
	{
		((unsigned char*)dst)[i] = ((unsigned char*)src)[i];
		i++;
	}
	return (0);
}

static void	*copipaster1(void *dst, const void *src, int c)
{
	return (copypasthelp(dst, src, c));
}

void		*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	size_t i;
	size_t j;

	i = 0;
	j = 0;
	if (n == 0)
		return (0);
	while (((unsigned char*)src)[i] != (unsigned char)c && (i < n - 1))
		i++;
	if (((unsigned char*)src)[i] == ((unsigned char)c))
		return (copipaster1(dst, src, c));
	else
		return (copipaster2(dst, src, n));
}
