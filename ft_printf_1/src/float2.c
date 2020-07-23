/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   float2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: couida <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/17 16:37:01 by couida            #+#    #+#             */
/*   Updated: 2020/01/17 16:37:08 by couida           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header_pf.h"

char	*ft_strcpy_pf(char *dst, const char *src)
{
	int i;

	i = 0;
	while (src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = src[i];
	return (&dst[i]);
}

void	print_float3(t_list_pf *list)
{
	int a;

	list->print[3] = list->leftfl;
	list->leftfl = NULL;
	a = sumlen(list);
	if (list->flag0[1])
		list->print[6] = create_string(' ', list->left - a);
	else if (list->flag0[0] == '0')
		list->print[2] = create_string('0', list->left - a);
	else
		list->print[0] = create_string(' ', list->left - a);
	printnum(list);
}

void	print_float2(t_list_pf *list)
{
	if (!list->point)
	{
		list->point = '.';
		list->right = 6;
	}
	if (!list->leftfl)
		list->leftfl = create_string('0', 1);
	if (!list->rightfl && list->right)
		list->rightfl = create_string('0', list->right);
	list->print[1] = create_string(list->flag0[2], 1);
	if (list->right || list->flag0[3])
		list->print[4] = create_string('.', 1);
	list->print[5] = rounding1(list);
	if (list->right == 0)
	{
		free(list->print[5]);
		list->print[5] = NULL;
	}
	print_float3(list);
}

void	print_float1(t_list_pf *list)
{
	t_double		num;
	unsigned long	mant1;
	int				exp1;
	char			*tmp;

	num.ld = list->fl;
	mant1 = num.s_parts.mant;
	exp1 = (num.s_parts.expon - 16383 - 63);
	list->flag0[2] = (num.s_parts.sign ? '-' : list->flag0[2]);
	tmp = NULL;
	if (inf_nan(num.s_parts.sign, mant1, num.s_parts.expon, list))
		return ;
	else if (exp1 >= 0)
		list->leftfl = conversion(mant1, exp1, 2);
	else if (exp1 >= -63)
	{
		list->leftfl = conversion(mant1 >> -exp1, 0, 2);
		tmp = conversion(mant1 & (power(2, -exp1) - 1), -exp1, 5);
	}
	else
		tmp = conversion(mant1, -exp1, 5);
	list->zero = create_string('0', -exp1 - ft_strlen_pf(tmp));
	list->rightfl = ft_strjoin(list->zero, tmp);
	free(tmp);
	print_float2(list);
}

void	float_f(t_list_pf *list, va_list ap)
{
	long double	f;

	if (list->flag1 != 5)
		f = va_arg(ap, double);
	else
		f = va_arg(ap, long double);
	list->fl = f;
	print_float1(list);
}
