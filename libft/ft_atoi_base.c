/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtristan <gtristan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 11:38:24 by gtristan          #+#    #+#             */
/*   Updated: 2019/10/21 09:18:44 by gtristan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_is_number(char c, int base)
{
	int i;

	if (c < 48 || (c > 57 && c < 65) || (c > 70 && c < 97) || c > 102)
		return (-1);
	if (c >= 48 && c <= 57)
		i = c - '0';
	else if (c >= 65 && c <= 70)
		i = c - 55;
	else if (c >= 97 && c <= 102)
		i = c - 87;
	if (base <= 16 && i < base)
		return (i);
	return (-1);
}

int			ft_atoi_base(const char *str, int str_base)
{
	long	a;
	int		i;
	int		sign;

	sign = 1;
	a = 0;
	while (ft_isspace(*str))
		str++;
	if (*str == '-')
	{
		sign = -1;
		str++;
	}
	else if (*str == '+')
		str++;
	while (str && (i = ft_is_number(*str, str_base)) >= 0)
	{
		a = a * str_base + i;
		str++;
	}
	if (*str)
		return (0);
	return (a * sign);
}
