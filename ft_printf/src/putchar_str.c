/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   putchar_str.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: couida <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/17 16:39:11 by couida            #+#    #+#             */
/*   Updated: 2020/01/17 16:39:15 by couida           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header_pf.h"

char	*get_result_str(void)
{
	return (add_char_to_output_buffer(0));
}

int		ft_putchar_pf(char c, int n)
{
	static int num = 0;

	if (n > 0)
	{
		while (n > 0)
		{
			add_char_to_output_buffer(c);
			n--;
			num++;
		}
	}
	else if (c == '@')
	{
		n = num;
		num = 0;
		return (n);
	}
	return (num);
}

size_t	ft_putstr_pf(char *s)
{
	size_t i;

	i = 0;
	if (!s)
		return (0);
	while (*s)
	{
		ft_putchar_pf(*s, 1);
		s++;
		i++;
	}
	return (i);
}

int		ft_strlen_pf(char *str)
{
	int i;

	i = 0;
	if (!str)
		return (0);
	else
	{
		while (str[i])
			i++;
		return (i);
	}
}

int		last_letter(char c)
{
	if (c == 'd' || c == 'i' || c == 'o' || c == 'u' || c == 'x' || c == 'X' \
	|| c == 'c' || c == 's' || c == 'p' || c == 'f' || c == '%' || c == 'z')
		return (1);
	else if ((c >= '0' && c <= '9') || c == '.' || c == '#' || c == '-' \
	|| c == '+' || c == ' ' || c == 'l' || c == 'h' || c == 'L' \
	|| c == 39 || c == '*' || c == '$')
		return (0);
	else
		return (-1);
}
