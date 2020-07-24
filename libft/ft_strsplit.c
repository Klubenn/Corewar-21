/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtapioca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 18:44:49 by gtapioca          #+#    #+#             */
/*   Updated: 2020/07/24 14:38:58 by gtapioca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../includes/libft.h"

static char	**deleter(char **ptr, int k)
{
	int g;
	int i;

	g = k;
	i = 0;
	while (k > 0)
	{
		ptr--;
		free(*ptr);
		k--;
	}
	free(ptr);
	ptr = NULL;
	return (ptr);
}

static char	**word_creator(char const *s, char **ptr, int i, int k)
{
	int j;

	j = 0;
	*ptr = (char *)malloc(sizeof(char) * (i + 1));
	if (!*ptr)
	{
		ptr = deleter(ptr, k);
		return (ptr);
	}
	while (j < i && *s != '\0')
	{
		(*ptr)[j] = *s;
		s++;
		j++;
	}
	(*ptr)[j] = '\0';
	ptr++;
	return (ptr);
}

static char	**word_array_creator(char const *s, char c, char **ptr)
{
	int i;
	int k;

	i = 0;
	k = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		while (s[i] != c && s[i] != '\0')
			i++;
		if (i)
		{
			k++;
			ptr = word_creator(s, ptr, i, k);
			if (!ptr)
				return (0);
			while (*s != c && *s != '\0')
				s++;
			i = 0;
		}
	}
	return (ptr);
}

static int	word_counter(char const *s, char c)
{
	int size;
	int f;

	f = 0;
	size = 0;
	while (s[f])
	{
		if ((s[f] == c && s[f - 1] != c) || (s[f] != c && s[f + 1] == '\0'))
			size++;
		f++;
	}
	return (size);
}

char		**ft_strsplit(char const *s, char c)
{
	char **ptr;
	char **ptr2;

	if (!s)
		return (0);
	ptr = (char **)malloc(sizeof(char *) * (word_counter(s, c) + 1));
	if (!ptr)
		return (0);
	ptr2 = ptr;
	ptr = word_array_creator(s, c, ptr);
	*ptr = NULL;
	return (ptr2);
}
