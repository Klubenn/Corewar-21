/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   oct.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: couida <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/17 16:38:15 by couida            #+#    #+#             */
/*   Updated: 2020/01/17 16:38:19 by couida           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header_pf.h"

char	*hash(t_list_pf *list)
{
	int		i;
	char	*str;

	if (list->letter == 'o')
		i = 1;
	else
		i = 2;
	str = (char *)malloc(sizeof(char) * (i + 1));
	str[i] = '\0';
	str[0] = '0';
	if (list->letter == 'x')
		str[1] = 'x';
	else if (list->letter == 'X')
		str[1] = 'X';
	return (str);
}

void	printnum_u2(t_list_pf *list, int sum)
{
	if (list->point)
	{
		if (list->letter == 'o')
			sum = sumlen(list);
		else
			sum = ft_strlen_pf(list->print[4]);
		list->print[3] = create_string('0', list->right - sum);
		sum = sumlen(list);
		if (list->flag0[1])
			list->print[5] = create_string(' ', list->left - sum);
		else
			list->print[0] = create_string(' ', list->left - sum);
	}
	else
	{
		sum = sumlen(list);
		if (list->flag0[1])
			list->print[5] = create_string(' ', list->left - sum);
		else if (list->flag0[0] == '0')
			list->print[3] = create_string('0', list->left - sum);
		else
			list->print[0] = create_string(' ', list->left - sum);
	}
	printnum(list);
}

void	printnum_u1(t_list_pf *list)
{
	int sum;

	if (list->flag0[3])
		list->print[2] = hash(list);
	list->print[4] = list->number;
	list->number = NULL;
	sum = 0;
	printnum_u2(list, sum);
}

void	oct_hex_u(t_list_pf *list, va_list ap, int base)
{
	unsigned long long i;

	if (list->letter == 'u')
		list->flag0[2] = 0;
	i = va_arg(ap, unsigned long long);
	if (list->flag1 != 0)
	{
		if (list->flag1 == 1)
			i = (unsigned short)i;
		else if (list->flag1 == 2)
			i = (unsigned char)i;
		else if (list->flag1 == 3)
			i = (unsigned long)i;
	}
	else
		i = (unsigned int)i;
	list->number = ft_itoa_base_u1(i, base, (list->letter == 'X'));
	if (i == 0 && list->right == 0 && list->point)
		zerocase_u1(list);
	else if (list->letter == 'u')
		printnum_d1(list);
	else if (i == 0 && list->flag0[3])
		zerocase_u2(list);
	else
		printnum_u1(list);
}
