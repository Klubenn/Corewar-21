/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtapioca <gtapioca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/04 20:29:29 by gtapioca          #+#    #+#             */
/*   Updated: 2019/09/19 19:16:42 by gtapioca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

static char	*locator(const char *haystack, const char *needle,
			size_t *mas, size_t len)
{
	size_t	j;
	char	*l;
	size_t	k;

	j = 0;
	k = mas[1];
	while (haystack[j] == needle[j] && k < len && haystack[j] && needle[j])
	{
		j++;
		k++;
	}
	if (mas[0] == j)
	{
		l = (char *)haystack;
		return (l);
	}
	return (0);
}

static char	*finder(const char *haystack, const char *needle, size_t len)
{
	size_t		mas[2];
	char		*l;

	mas[0] = 0;
	mas[1] = 0;
	while (needle[mas[0]] != 0)
		mas[0]++;
	while (*haystack && mas[1] < len)
	{
		if (*haystack == *needle)
			if ((l = locator(haystack, needle, mas, len)))
				return (l);
		haystack++;
		mas[1]++;
	}
	return (0);
}

char		*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	if (!(*needle))
		return ((char *)haystack);
	if (!(*haystack))
		return (0);
	return (finder(haystack, needle, len));
}
