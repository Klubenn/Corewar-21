/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_char.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: couida <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/17 16:39:32 by couida            #+#    #+#             */
/*   Updated: 2020/01/17 16:39:34 by couida           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header_pf.h"

void	percent(t_list_pf *list)
{
	list->print[2] = create_string('%', 1);
	if (list->left)
	{
		if (list->flag0[1])
			list->print[3] = create_string(' ', list->left - 1);
		else
			list->print[1] = create_string(list->flag0[0], list->left - 1);
	}
	printnum(list);
}

void	character(t_list_pf *list, va_list ap)
{
	char c;
	char *str;

	c = va_arg(ap, int);
	str = create_string(' ', list->left - 1);
	if (list->flag0[1])
	{
		ft_putchar_pf(c, 1);
		ft_putstr_pf(str);
	}
	else
	{
		ft_putstr_pf(str);
		ft_putchar_pf(c, 1);
	}
	free(str);
}

size_t	ft_putstr_len_pf(char *str, size_t len)
{
	size_t i;

	i = 0;
	if (!str)
		return (0);
	while (len > 0 && *str)
	{
		ft_putchar_pf(*str, 1);
		str++;
		len--;
		i++;
	}
	return (i);
}

void	string2(t_list_pf *list, char *str)
{
	int i;

	if (list->flag0[1])
	{
		i = ft_putstr_len_pf(str, list->right);
		ft_putchar_pf(' ', list->left - i);
	}
	else
	{
		i = list->right - ft_strlen_pf(str);
		if (i <= 0)
		{
			ft_putchar_pf(list->flag0[0], list->left - list->right);
			ft_putstr_len_pf(str, list->right);
		}
		else
		{
			ft_putchar_pf(list->flag0[0], list->left - list->right + i);
			ft_putstr_pf(str);
		}
	}
}
