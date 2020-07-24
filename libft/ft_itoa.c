/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtapioca <gtapioca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/04 20:29:29 by gtapioca          #+#    #+#             */
/*   Updated: 2019/09/19 17:30:48 by gtapioca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static char	*itoa_helper_sign_plus(int n, int i)
{
	char	*ptr;

	ptr = (char *)malloc(sizeof(char) * (1 + i));
	if (!ptr)
		return (0);
	ptr[i] = '\0';
	while (i > 0)
	{
		ptr[i - 1] = (n % 10) + '0';
		n = n / 10;
		i--;
	}
	return (ptr);
}

static char	*itoa_helper_zero(void)
{
	char *ptr;

	ptr = (char *)malloc(sizeof(char) * (2));
	if (!ptr)
		return (0);
	ptr[0] = '0';
	ptr[1] = '\0';
	return (ptr);
}

static char	*itoa_helper_sign_minus(int n, int i)
{
	char	*ptr;

	ptr = (char *)malloc(sizeof(char) * (2 + i));
	if (!ptr)
		return (0);
	ptr[i + 1] = '\0';
	n *= -1;
	while (i > 0)
	{
		ptr[i] = (n % 10) + '0';
		n = n / 10;
		i--;
	}
	ptr[0] = '-';
	return (ptr);
}

static char	*itoa_helper_int_min(void)
{
	char	*ptr;
	int		n;
	int		i;

	n = -2147483648;
	i = 10;
	ptr = (char *)malloc(sizeof(char) * (12));
	if (!ptr)
		return (0);
	while (i > 0)
	{
		ptr[i] = ((n % 10) * (-1)) + '0';
		i--;
		n = n / 10;
	}
	ptr[0] = '-';
	ptr[11] = '\0';
	return (ptr);
}

char		*ft_itoa(int n)
{
	int		sign;
	int		i;
	char	*ptr;
	int		k;

	sign = 1;
	i = 0;
	if (n == 0)
		return (itoa_helper_zero());
	if (n < 0)
		sign = -1;
	k = n;
	if (n == -2147483648)
		return (itoa_helper_int_min());
	while ((k % 10) || (k / 10))
	{
		k = k / 10;
		i++;
	}
	if (sign == -1)
		return (itoa_helper_sign_minus(n, i));
	else
		return (itoa_helper_sign_plus(n, i));
	return (ptr);
}
