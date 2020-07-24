/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   decimal.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: couida <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/17 16:36:32 by couida            #+#    #+#             */
/*   Updated: 2020/01/17 16:36:37 by couida           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header_pf.h"

void	zerocase(t_list_pf *list)
{
	int i;

	i = -1;
	if (list->flag0[1])
	{
		if (list->flag0[2])
		{
			ft_putchar_pf(list->flag0[2], 1);
			i++;
		}
		while (++i < list->left)
			ft_putchar_pf(' ', 1);
	}
	else
	{
		if (list->flag0[2])
			i++;
		while (++i < list->left)
			ft_putchar_pf(' ', 1);
		if (list->flag0[2])
			ft_putchar_pf(list->flag0[2], 1);
	}
}

void	zerocase_u1(t_list_pf *list)
{
	int i;

	i = -1;
	if (!list->flag0[3] || list->letter != 'o')
	{
		list->flag0[2] = 0;
		zerocase(list);
	}
	else if (list->flag0[3] && list->letter == 'o')
	{
		if (list->flag0[1])
			ft_putchar_pf('0', 1);
		i++;
		while (++i < list->left)
			ft_putchar_pf(' ', 1);
		if (!list->flag0[1])
			ft_putchar_pf('0', 1);
	}
}

void	zerocase_u2(t_list_pf *list)
{
	int sum;

	if (list->right)
		list->print[2] = create_string('0', list->right);
	else if (list->flag0[0] == ' ' || list->flag0[1])
		list->print[2] = create_string('0', 1);
	else if (list->flag0[0] == '0' && !list->flag0[1])
		list->print[2] = create_string('0', list->left);
	sum = sumlen(list);
	if (list->flag0[1])
		list->print[3] = create_string(' ', list->left - sum);
	else
		list->print[1] = create_string(' ', list->left - sum);
	printnum(list);
}

void	decimal(t_list_pf *list, va_list ap)
{
	long long	i;

	i = va_arg(ap, long long);
	if (list->flag1 != 0)
	{
		if (list->flag1 == 1)
			i = (short)i;
		else if (list->flag1 == 2)
			i = (signed char)i;
		else if (list->flag1 == 3)
			i = (long)i;
	}
	else
		i = (int)i;
	list->number = ft_itoa_pf(i, list);
	if (i == 0 && list->right == 0 && list->point)
		zerocase(list);
	else
		printnum_d1(list);
}
