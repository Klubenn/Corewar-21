/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtristan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/12 11:14:49 by gtristan          #+#    #+#             */
/*   Updated: 2019/09/12 14:42:40 by gtristan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_int_size(long long n, int sign)
{
	int i;

	i = 0;
	if (n == 0)
		return (1);
	while (n > 0)
	{
		n = n / 10;
		i++;
	}
	if (sign == -1)
		i++;
	return (i);
}

char		*ft_itoa(int n)
{
	char		*s;
	int			k;
	int			sign;
	long long	new;

	new = (long long)n;
	sign = (new < 0) ? -1 : 1;
	new = (new < 0) ? -new : new;
	k = ft_int_size(new, sign);
	if (!(s = (char *)malloc(sizeof(char) * (k + 1))))
		return (NULL);
	s[k--] = '\0';
	if (new == 0)
		s[0] = '0';
	while (new > 0)
	{
		s[k--] = new % 10 + '0';
		new = new / 10;
	}
	if (sign == -1)
		s[k] = '-';
	return (s);
}
