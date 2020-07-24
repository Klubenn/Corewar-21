/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtristan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/12 10:05:21 by gtristan          #+#    #+#             */
/*   Updated: 2019/09/15 15:42:34 by gtristan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_words(char const *s, char c)
{
	int		i;

	i = 0;
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (*s && *s != c)
		{
			i++;
			while (*s && *s != c)
				s++;
		}
	}
	return (i);
}

static char	*ft_word_size(char const *s, char c)
{
	char	*word;
	size_t	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	word = (char *)malloc(sizeof(char) * (i + 1));
	if (!word || (i + 1 == 0))
		return (NULL);
	i = 0;
	while (s[i] && s[i] != c)
	{
		word[i] = s[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

static char	**ft_break(char **str, int i)
{
	while (i >= 0)
	{
		free(str[i]);
		i--;
	}
	return (NULL);
}

char		**ft_strsplit(char const *s, char c)
{
	size_t	num;
	char	**str;
	int		i;

	if (s == NULL)
		return (NULL);
	num = ft_words(s, c);
	str = (char **)malloc(sizeof(char*) * (num + 1));
	if (!str || (num + 1 == 0))
		return (NULL);
	i = 0;
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (*s && *s != c)
		{
			if (!(str[i++] = ft_word_size(s, c)))
				return (ft_break(str, i));
			while (*s && *s != c)
				s++;
		}
	}
	str[i] = NULL;
	return (str);
}
