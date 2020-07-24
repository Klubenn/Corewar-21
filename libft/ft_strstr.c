/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtapioca <gtapioca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/04 20:29:29 by gtapioca          #+#    #+#             */
/*   Updated: 2019/09/18 22:37:24 by gtapioca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static char	*locator(const char *haystack, const char *needle, int i)
{
	int		j;
	char	*l;

	j = 0;
	while (haystack[j] == needle[j] && haystack[j] && needle[j])
		j++;
	if (i == j + 1)
	{
		l = (char *)haystack;
		return (l);
	}
	return (0);
}

static char	*finder(const char *haystack, const char *needle)
{
	int		i;
	int		j;
	char	*l;

	j = 0;
	i = 0;
	while (needle[i] != 0)
		++i;
	++i;
	while (*haystack)
	{
		if (*haystack == *needle)
			if ((l = locator(haystack, needle, i)))
				return (l);
		haystack++;
	}
	return (0);
}

char		*ft_strstr(const char *haystack, const char *needle)
{
	if (!(*needle))
		return ((char *)haystack);
	if (!(*haystack))
		return (0);
	return (finder(haystack, needle));
}
