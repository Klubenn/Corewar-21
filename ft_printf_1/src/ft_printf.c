/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtapioca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/17 16:37:51 by couida            #+#    #+#             */
/*   Updated: 2020/07/24 15:56:44 by gtapioca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header_pf.h"

void	separation(const char *format, va_list ap)
{
	int		i;
	int		num;
	char	*ch;

	num = 0;
	ch = (char *)format;
	while (*ch != '\0')
	{
		while (*ch && *ch != '%')
		{
			if (*ch == '{' && (i = print_color(ch)))
			{
				ch += i;
				continue ;
			}
			ft_putchar_pf(*ch, 1);
			ch++;
			num++;
		}
		if (*ch == '%')
		{
			ch++;
			ch += parsing1(ch, ap);
		}
	}
}

int		ft_printf(const char *format, ...)
{
	va_list		ap;
	char		*res_str;

	va_start(ap, format);
	separation(format, ap);
	va_end(ap);
	res_str = get_result_str();
	if (res_str)
	{
		write(get_fd(), res_str, ft_strlen(res_str));
		free(res_str);
	}
	return (ft_putchar_pf('@', 0));
}
