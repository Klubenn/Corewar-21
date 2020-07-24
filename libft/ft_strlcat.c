/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtapioca <gtapioca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/04 20:29:29 by gtapioca          #+#    #+#             */
/*   Updated: 2019/09/18 23:26:12 by gtapioca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

static size_t	counter2(const char *src)
{
	size_t i;

	i = 0;
	while (src[i])
		++i;
	++i;
	return (i);
}

static size_t	counter1(char *dst)
{
	size_t i;

	i = 0;
	while (dst[i])
		++i;
	++i;
	return (i);
}

static void		concatinator2(char *dst, const char *src, size_t i)
{
	size_t j;

	j = 0;
	while (src[j])
	{
		dst[i] = src[j];
		i++;
		j++;
	}
	dst[i] = '\0';
}

static void		concatinator1(char *dst, const char *src, size_t size, size_t i)
{
	size_t j;

	j = 0;
	while (i < size - 1)
	{
		dst[i] = src[j];
		i++;
		j++;
	}
	dst[i] = '\0';
}

size_t			ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t i;
	size_t j;
	size_t c;
	size_t l;

	i = counter1(dst);
	j = counter2(src);
	if (size < i)
		return (j - 1 + size);
	c = i;
	l = j;
	--i;
	if (size <= (c + l - 1))
	{
		concatinator1(dst, src, size, i);
		return (c + l - 2);
	}
	concatinator2(dst, src, i);
	return (c + l - 2);
}
