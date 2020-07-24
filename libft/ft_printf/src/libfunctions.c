/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libfunctions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtapioca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/17 16:38:03 by couida            #+#    #+#             */
/*   Updated: 2020/07/24 15:56:44 by gtapioca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header_pf.h"

size_t	ft_strlen(const char *s)
{
	size_t i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int		ft_atoi(const char *str)
{
	size_t				i;
	unsigned long long	number;
	int					minus_number;

	i = 0;
	minus_number = 1;
	number = 0;
	while (str[i] && (str[i] == ' ' || (str[i] > 8 && str[i] < 14)))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			minus_number = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
		number = number * 10 + str[i++] - '0';
	if (number > 9223372036854775807 && minus_number == -1)
		return (0);
	if (number > 9223372036854775807 && minus_number == 1)
		return (-1);
	if (minus_number == -1)
		return ((int)(number * -1));
	else
		return ((int)number);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	size_t	j;
	char	*fresh;

	if (!s1 || !s2)
		return (NULL);
	i = (size_t)(ft_strlen(s1) + ft_strlen(s2));
	if ((fresh = (char*)malloc(sizeof(char) * (i + 1))))
	{
		fresh[i] = '\0';
		j = 0;
		i = 0;
		while (s1 && s1[j])
		{
			fresh[j] = s1[j];
			j++;
		}
		while (s2 && s2[i])
		{
			fresh[i + j] = s2[i];
			i++;
		}
		return (fresh);
	}
	return (NULL);
}

char	*ft_strncpy(char *dst, const char *src, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 1;
	while (i < len)
	{
		if (src[i] != '\0' && j != 0)
			dst[i] = src[i];
		else
		{
			j = 0;
			dst[i] = '\0';
		}
		i++;
	}
	return (dst);
}

char	*ft_strcpy(char *dst, const char *src)
{
	size_t i;

	i = 0;
	while (src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}
