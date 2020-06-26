/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analysis.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: couida <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/17 16:35:56 by couida            #+#    #+#             */
/*   Updated: 2020/01/17 16:36:15 by couida           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header_pf.h"

void	string1(t_list_pf *list, va_list ap)
{
	char	*str;
	int		i;

	str = va_arg(ap, char *);
	if (!str)
		str = "(null)";
	if (list->point)
		string2(list, str);
	else
	{
		if (list->flag0[1])
		{
			i = ft_putstr_pf(str);
			ft_putchar_pf(' ', list->left - i);
		}
		else
		{
			ft_putchar_pf(list->flag0[0], list->left - ft_strlen_pf(str));
			ft_putstr_pf(str);
		}
	}
}

char	*ft_makestr(char *str)
{
	int		i;
	char	*strnew;

	i = ft_strlen(str);
	strnew = (char *)malloc(sizeof(char) * (i + 1));
	strnew[i] = '\0';
	while (--i >= 0)
		strnew[i] = str[i];
	return (strnew);
}

void	pointer(t_list_pf *list, va_list ap)
{
	unsigned long long	i;
	int					sum;

	i = va_arg(ap, unsigned long long);
	if (i == 0)
		list->print[1] = ft_makestr("0x0");
	else
	{
		list->print[1] = ft_makestr("0x");
		list->print[2] = ft_itoa_base_u1(i, 16, 0);
	}
	sum = sumlen(list);
	if (list->flag0[1])
		list->print[3] = create_string(' ', list->left - sum);
	else
		list->print[0] = create_string(' ', list->left - sum);
	printnum(list);
}

void	analysis(t_list_pf *list, va_list ap)
{
	if (list->letter == 'd' || list->letter == 'i')
		decimal(list, ap);
	else if (list->letter == 'o')
		oct_hex_u(list, ap, 8);
	else if (list->letter == 'x' || list->letter == 'X')
		oct_hex_u(list, ap, 16);
	else if (list->letter == 'u')
		oct_hex_u(list, ap, 10);
	else if (list->letter == '%')
		percent(list);
	else if (list->letter == 'c')
		character(list, ap);
	else if (list->letter == 's')
		string1(list, ap);
	else if (list->letter == 'p')
		pointer(list, ap);
	else if (list->letter == 'f')
		float_f(list, ap);
}
